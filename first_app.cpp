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
#include "include/engine/Core.h"

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
                sizeof(Engine::GlobalUbo),
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

    auto viewerObject = Engine::GameObject::createGameObject("Camera");
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
        camera.setProspectiveProjection(glm::radians(80.f), aspectRatio, .1f, 25.f);

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
            Engine::GlobalUbo ubo{};
            ubo.projection = camera.getProjection();
            ubo.view = camera.getView();
            ubo.inverseView = camera.getInverseViewMatrix();
            pointLightSystem.update(frameInfo, ubo);
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

    vkDeviceWaitIdle(device.getVkDevice());
}

void FirstApp::loadGameObjects() {
    std::ifstream i("../json/game_state.json");
    json j;
    i >> j;
    for (auto &it: j) {
        std::cout << "Loading model: ";
        if (it["model"]["file_name"].is_null()) {
            // Light
            std::cout << "light\n";
            auto pointLight = Engine::GameObject::createPointLight(it["intensity"].get<float>());
            pointLight.name = it["name"].get<std::string>();
            pointLight.color = glm::vec3(it["transform"]["color"]["x"].get<float>(),
                                         it["transform"]["color"]["y"].get<float>(),
                                         it["transform"]["color"]["z"].get<float>());
            pointLight.transform.translation = glm::vec3(it["transform"]["translation"]["x"].get<float>(),
                                                         it["transform"]["translation"]["y"].get<float>(),
                                                         it["transform"]["translation"]["z"].get<float>());
            pointLight.transform.scale = glm::vec3(it["transform"]["scale"]["x"].get<float>(),
                                                   it["transform"]["scale"]["y"].get<float>(),
                                                   it["transform"]["scale"]["z"].get<float>());
            gameObjects.emplace(pointLight.getId(), std::move(pointLight));
        } else {
            // Object
            std::cout << "Object\n";
            std::shared_ptr<Engine::Model> model = Engine::Model::createModelFromFile(device,
                                                                                      it["model"]["file_name"].get<std::string>().c_str());
            std::string name = it["model"]["file_name"].get<std::string>().substr(10);
            auto obj = Engine::GameObject::createGameObject(name.c_str());
            obj.model = model;
            obj.name = it["name"].get<std::string>();
            obj.color = glm::vec3(it["transform"]["color"]["x"].get<float>(),
                                  it["transform"]["color"]["y"].get<float>(),
                                  it["transform"]["color"]["z"].get<float>());
            obj.transform.translation = glm::vec3(it["transform"]["translation"]["x"].get<float>(),
                                                  it["transform"]["translation"]["y"].get<float>(),
                                                  it["transform"]["translation"]["z"].get<float>());
            obj.transform.scale = glm::vec3(it["transform"]["scale"]["x"].get<float>(),
                                            it["transform"]["scale"]["y"].get<float>(),
                                            it["transform"]["scale"]["z"].get<float>());
            obj.transform.rotation = glm::vec3(it["transform"]["rotation"]["x"].get<float>(),
                                               it["transform"]["rotation"]["y"].get<float>(),
                                               it["transform"]["rotation"]["z"].get<float>());
            gameObjects.emplace(obj.getId(), std::move(obj));
        }
    }
}