//
// Created by Jacopo Beragnoli on 12/04/22.
//

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/constants.hpp>
#include <array>
#include "first_app.h"
#include "include/engine/RenderSystem.h"

FirstApp::FirstApp() {
    loadGameObjects();
}

FirstApp::~FirstApp() {}

void FirstApp::run() {
    Engine::RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    Engine::Camera camera{};
    while (!window.shouldClose()) {
        glfwPollEvents();

        float aspectRatio = renderer.getAspectRatio();
        //camera.setOrthographicProjection(-aspectRatio, aspectRatio, -1.f, 1.f, -1.f, 1.f);
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
    std::vector<Engine::Model::Vertex> vertices{

            // left face (white)
            {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
            {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f},   {.9f, .9f, .9f}},
            {{-.5f, -.5f, -.5f},  {.9f, .9f, .9f}},
            {{-.5f, .5f,  -.5f},  {.9f, .9f, .9f}},
            {{-.5f, .5f,  .5f},   {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f,  -.5f, -.5f},  {.8f, .8f, .9f}},
            {{.5f,  .5f,  .5f},   {.2f, .8f, .9f}},
            {{.5f,  -.5f, .5f},   {.4f, .7f, .9f}},
            {{.5f,  -.5f, -.5f},  {.5f, .8f, .9f}},
            {{.5f,  .5f,  -.5f},  {.2f, .2f, .9f}},
            {{.5f,  .5f,  .5f},   {.5f, .5f, .9f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
            {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f},   {.9f, .6f, .1f}},
            {{-.5f, -.5f, -.5f},  {.9f, .6f, .1f}},
            {{.5f,  -.5f, -.5f},  {.9f, .6f, .1f}},
            {{.5f,  -.5f, .5f},   {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
            {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},
            {{-.5f, .5f,  .5f},   {.8f, .1f, .1f}},
            {{-.5f, .5f,  -.5f},  {.8f, .1f, .1f}},
            {{.5f,  .5f,  -.5f},  {.8f, .1f, .1f}},
            {{.5f,  .5f,  .5f},   {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
            {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},
            {{-.5f, .5f,  0.5f},  {.1f, .1f, .8f}},
            {{-.5f, -.5f, 0.5f},  {.1f, .1f, .8f}},
            {{.5f,  -.5f, 0.5f},  {.1f, .1f, .8f}},
            {{.5f,  .5f,  0.5f},  {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f,  -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f,  -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f,  .5f,  -0.5f}, {.1f, .8f, .1f}},

    };
    for (auto &v: vertices) {
        v.position += offset;
    }
    return std::make_unique<Engine::Model>(device, vertices);
}

void FirstApp::loadGameObjects() {
    std::shared_ptr<Engine::Model> model = createCubeModel(device, {.0f, .0f, .0f});

    auto cube = Engine::GameObject::createGameObject();
    cube.model = model;
    cube.transform.translation = {.0f, .0f, 7.5f};
    cube.transform.scale = {.5f, .5f, .5f};

    gameObjects.push_back(std::move(cube));
}