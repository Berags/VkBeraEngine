//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../include/engine/MainLoop.h"
#include <string>
#include <stdexcept>

namespace Engine {
    MainLoop::MainLoop(Engine::Window *window) : window(window) {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    MainLoop::~MainLoop() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void MainLoop::start() {

        // call to the update method that will draw graphics to the screen
        update();

        // when update is done we call the stop function that deletes the window
        stop();
    }

    void MainLoop::stop() {
        delete window;
    }

    void MainLoop::update() const {
        while (!window->shouldClose()) {
            // Calling the main render function
            render();

            // Swap front and back buffers
            window->swapBuffers();

            // Poll for and process events
            glfwPollEvents();
        }
    }

    void MainLoop::render() {

    }

    void MainLoop::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!"); // TODO: create error class
        }
    }

    void MainLoop::createPipeline() {
        auto pipeLineConfig = Pipeline::defaultConfigInfo(swapChain.width(), swapChain.height());
        pipeLineConfig.renderPass = swapChain.getRenderPass();
        pipeLineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Pipeline>(device, "../shaders/simple_shader.vert.spv",
                                              "../shaders/simple_shader.frag.spv",
                                              pipeLineConfig);

    }

    void MainLoop::createCommandBuffers() {

    }

    void MainLoop::drawFrame() {

    }
}