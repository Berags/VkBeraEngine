//
// Created by Jacopo Beragnoli on 12/04/22.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/constants.hpp>
#include <array>
#include <chrono>
#include <numeric>

#include "Application.h"
#include "include/engine/Core.h"
#include "include/game/entities/Test.h"
#include "include/game/entities/Player.h"
#include "include/game/components/GameObjectComponent.h"
#include "include/game/components/KeyboardInputComponent.h"
#include "include/game/components/HealthComponent.h"
#include "include/game/entities/Enemy.h"

Application::Application() {
    globalPool = Engine::DescriptorPool::Builder(device)
            .setMaxSets(Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();
    Engine::Scene::load(gameObjects, device);
}

Application::~Application() = default;

void Application::run() {
    Engine::ImGuiManager imGui{window, device, renderer.getSwapChainRenderPass(), renderer.getImageCount()};
    Engine::ECS::EntityManager entityManager{};

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

    auto viewerObject = Engine::GameObjectFactory::createGameObject("Camera");
    auto player = entityManager.createNewEntity<Game::Entities::Player>();
    player.addComponent<Game::Components::KeyboardInputComponent>(window, viewerObject);
    player.addComponent<Game::Components::HealthComponent>();

    viewerObject.transform.translation.z = -2.5f;

    auto currentTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        frameTime = glm::min(frameTime, 1.f / 60.f);

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
                    gameObjects,
            };
            // Update
            Engine::GlobalUbo ubo{};
            ubo.projection = camera.getProjection();
            ubo.view = camera.getView();
            ubo.inverseView = camera.getInverseViewMatrix();
            pointLightSystem.update(frameInfo, ubo);
            uboBuffers[frameIndex]->writeToBuffer(&ubo);
            uboBuffers[frameIndex]->flush();

            entityManager.updateEntities(frameInfo);

            // Render
            renderer.beginSwapChainRenderPass(commandBuffer);

            // Rendering order matters
            // First we want to render all solid objects
            // Then all semi-transparent objects
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