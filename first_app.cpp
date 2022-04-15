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

// temporary helper function, creates a 1x1x1 cube centered at offset
std::unique_ptr<Engine::Model> createCubeModel(Engine::Device &device, glm::vec3 offset) {
    Engine::Model::Data modelBuilder{};
    modelBuilder.vertices = {
            // left face (white)
            {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
            {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f},   {.9f, .9f, .9f}},
            {{-.5f, .5f,  -.5f},  {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f,  -.5f, -.5f},  {.8f, .8f, .1f}},
            {{.5f,  .5f,  .5f},   {.8f, .8f, .1f}},
            {{.5f,  -.5f, .5f},   {.8f, .8f, .1f}},
            {{.5f,  .5f,  -.5f},  {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
            {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f},   {.9f, .6f, .1f}},
            {{.5f,  -.5f, -.5f},  {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
            {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},
            {{-.5f, .5f,  .5f},   {.8f, .1f, .1f}},
            {{.5f,  .5f,  -.5f},  {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
            {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},
            {{-.5f, .5f,  0.5f},  {.1f, .1f, .8f}},
            {{.5f,  -.5f, 0.5f},  {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f,  -0.5f}, {.1f, .8f, .1f}},
            {{.5f,  -.5f, -0.5f}, {.1f, .8f, .1f}},
    };
    for (auto &v: modelBuilder.vertices) {
        v.position += offset;
    }

    modelBuilder.indices = {0, 1, 2, 0, 3, 1, 4, 5, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9,
                            12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21};

    return std::make_unique<Engine::Model>(device, modelBuilder);
}

void FirstApp::loadGameObjects() {
    std::shared_ptr<Engine::Model> model = createCubeModel(device, {.0f, .0f, .0f});

    auto cube = Engine::GameObject::createGameObject();
    cube.model = model;
    cube.transform.translation = {.0f, .0f, 2.5f};
    cube.transform.scale = {.5f, .5f, .5f};

    gameObjects.push_back(std::move(cube));
}