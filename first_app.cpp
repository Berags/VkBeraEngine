//
// Created by Jacopo Beragnoli on 12/04/22.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/constants.hpp>
#include <array>
#include <chrono>

#include "first_app.h"
#include "include/engine/RenderSystem.h"
#include "include/engine/KeyboardMovementController.h"

FirstApp::FirstApp() {
    loadGameObjects();
}

FirstApp::~FirstApp() = default;

void FirstApp::run() {
    Engine::RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    Engine::Camera camera{};
    //camera.setViewDirection(glm::vec3(0.f), glm::vec3(.5f, .0f, 1.f));
    camera.setViewTarget(glm::vec3(-1.f, -2.f, 6.f), glm::vec3(.0f, .0f, 2.5f));

    auto viewerObject = Engine::GameObject::createGameObject();
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
        camera.setProspectiveProjection(glm::radians(50.f), aspectRatio, .1f, 10.f);

        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void FirstApp::loadGameObjects() {
    std::shared_ptr<Engine::Model> model = Engine::Model::createModelFromFile(device, "../models/viking_room.obj");

    auto cube = Engine::GameObject::createGameObject();
    cube.model = model;
    cube.transform.translation = {.0f, .0f, 2.5f};
    cube.transform.rotation = {glm::half_pi<float>(), glm::half_pi<float>(), .0f};
    cube.transform.scale = {.8f, .8f, .8f};

    gameObjects.push_back(std::move(cube));
}