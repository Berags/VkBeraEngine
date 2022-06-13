//
// Created by Jacopo Beragnoli on 12/04/22.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <chrono>
#include <numeric>

#include "Application.h"
#include "include/game/entities/Player.h"
#include "include/game/components/KeyboardInputComponent.h"
#include "include/game/components/HealthComponent.h"
#include "include/game/components/GameObjectComponent.h"
#include "include/engine/Scene.h"
#include "include/engine/GameObjectFactory.h"
#include "include/engine/ImGuiManager.h"
#include "include/engine/ecs/EntityManager.h"
#include "include/engine/MousePicker.h"
#include "include/engine/systems/PointLightSystem.h"
#include "include/engine/systems/RenderSystem.h"

Application::Application() {
    globalPool = Engine::DescriptorPool::Builder(device)
            .setMaxSets(Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Engine::SwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();
    Engine::Scene::loadTextures(textureStorage);
    Engine::Scene::load(gameObjects, device);
}

Application::~Application() = default;

void Application::run() {
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

    auto textureSetLayout = Engine::DescriptorSetLayout::Builder(device)
            .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
            .build();

    std::vector<VkDescriptorSet> descriptorSets{Engine::SwapChain::MAX_FRAMES_IN_FLIGHT};

    Engine::RenderSystem renderSystem{device,
                                      textureStorage,
                                      renderer.getSwapChainRenderPass(),
                                      *globalSetLayout};
    Engine::PointLightSystem pointLightSystem{device, renderer.getSwapChainRenderPass(),
                                              globalSetLayout->getDescriptorSetLayout()};
    Engine::Camera camera{};
    camera.setViewTarget(glm::vec3(-1.f, -2.f, 6.f), glm::vec3(.0f, .0f, 2.5f));
    Engine::Editor::MousePicker mousePicker{window, camera, camera.getProjection()};
    Engine::ImGuiManager imGui{window, camera, device, renderer.getSwapChainRenderPass(), renderer.getImageCount()};

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

            mousePicker.update(); // Updated mouse ray casting

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