//
// Created by Jacopo Beragnoli on 12/04/22.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/constants.hpp>
#include <array>
#include <chrono>
#include <numeric>

#include "first_app.h"
#include "include/engine/systems/RenderSystem.h"
#include "include/engine/KeyboardMovementController.h"
#include "include/engine/ImGuiManager.h"
#include "include/engine/systems/PointLightSystem.h"

struct GlobalUbo {
    glm::mat4 projection{1.f};
    glm::mat4 view{1.f};
    glm::vec4 ambientColor{1.f, 1.f, 1.f, .02f}; // w is light intensity
    glm::vec3 lightPosition{-1.f};
    alignas(16) glm::vec4 lightColor{1.f}; // w is light intensity
};

FirstApp::FirstApp() {
    globalPool = Engine::DescriptorPool::Builder(device)
            .setMaxSets(Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();
    loadGameObjects();
}

FirstApp::~FirstApp() = default;

void FirstApp::run() {
    Engine::ImGuiManager imGui{window, device, renderer.getSwapChainRenderPass(), renderer.getImageCount()};

    std::vector<std::unique_ptr<Engine::Buffer>> uboBuffers(Engine::SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (auto &uboBuffer: uboBuffers) {
        uboBuffer = std::make_unique<Engine::Buffer>(
                device,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        uboBuffer->map();
    }

    auto globalSetLayout = Engine::DescriptorSetLayout::Builder(device)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

    std::vector<VkDescriptorSet> globalDescriptorSets(Engine::SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < globalDescriptorSets.size(); i++) {
        auto bufferInfo = uboBuffers[i]->descriptorInfo();
        Engine::DescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
    }

    Engine::RenderSystem renderSystem{device, renderer.getSwapChainRenderPass(),
                                      globalSetLayout->getDescriptorSetLayout()};
    Engine::PointLightSystem pointLightSystem{device, renderer.getSwapChainRenderPass(),
                                              globalSetLayout->getDescriptorSetLayout()};
    Engine::Camera camera{};
    camera.setViewTarget(glm::vec3(-1.f, -2.f, 6.f), glm::vec3(.0f, .0f, 2.5f));

    auto viewerObject = Engine::GameObject::createGameObject((std::string &) "Camera");
    viewerObject.transform.translation.z = -2.5f;
    Engine::KeyboardMovementController cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        frameTime = glm::min(frameTime, 1.f / 60.f);

        cameraController.moveInPlaneXZ(window.getGlfwWindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspectRatio = renderer.getAspectRatio();
        camera.setProspectiveProjection(glm::radians(50.f), aspectRatio, .1f, 100.f);

        if (auto commandBuffer = renderer.beginFrame()) {
            imGui.newFrame();

            int frameIndex = renderer.getFrameIndex();
            Engine::FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects
            };
            // Update
            GlobalUbo ubo{};
            ubo.projection = camera.getProjection();
            ubo.view = camera.getView();
            uboBuffers[frameIndex]->writeToBuffer(&ubo);
            uboBuffers[frameIndex]->flush();

            // Render
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(frameInfo);
            pointLightSystem.render(frameInfo);

            // ImGui rendering
            imGui.run(frameInfo);
            imGui.render(commandBuffer);

            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void FirstApp::loadGameObjects() {
    std::shared_ptr<Engine::Model> model = Engine::Model::createModelFromFile(device, "../models/viking_room.obj");
    std::shared_ptr<Engine::Model> hellknight = Engine::Model::createModelFromFile(device,
                                                                                   "../models/Hellknight_LATEST.obj");
    std::shared_ptr<Engine::Model> quadModel = Engine::Model::createModelFromFile(device, "../models/quad.obj");

    auto cube = Engine::GameObject::createGameObject((std::string &) "Viking Room");
    cube.model = model;
    cube.transform.translation = {.0f, .0f, .0f};
    cube.transform.rotation = {glm::half_pi<float>(), glm::half_pi<float>(), .0f};
    cube.transform.scale = {.8f, .8f, .8f};

    auto obj = Engine::GameObject::createGameObject((std::string &) "Hell Knight");
    obj.model = hellknight;
    obj.transform.translation = {1.4f, .0f, .0f};
    obj.transform.rotation = {.0f, glm::pi<float>(), glm::pi<float>()};
    obj.transform.scale = {.4f, .4f, .4f};

    auto floor = Engine::GameObject::createGameObject((std::string &) "Floor");
    floor.model = quadModel;
    floor.transform.translation = {6.0f, .5f, .0f};
    floor.transform.scale = {50.f, 1.f, 50.f};

    gameObjects.emplace(cube.getId(), std::move(cube));
    gameObjects.emplace(obj.getId(), std::move(obj));
    gameObjects.emplace(floor.getId(), std::move(floor));
}