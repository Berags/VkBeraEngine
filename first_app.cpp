//
// Created by Jacopo Beragnoli on 12/04/22.
//

#include <array>
#include "first_app.h"

FirstApp::FirstApp() {
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
}

FirstApp::~FirstApp() { vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr); }

void FirstApp::run() {
    while (!lveWindow.shouldClose()) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(lveDevice.device());
}

void FirstApp::createPipelineLayout() {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

void FirstApp::createPipeline() {
    Engine::PipelineConfigInfo pipelineConfig{};
    Engine::Pipeline::defaultConfigInfo(
            pipelineConfig);
    pipelineConfig.renderPass = lveSwapChain->getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    lvePipeline = std::make_unique<Engine::Pipeline>(
            lveDevice,
            "../shaders/simple_shader.vert.spv",
            "../shaders/simple_shader.frag.spv",
            pipelineConfig);
}

void FirstApp::createCommandBuffers() {
    commandBuffers.resize(lveSwapChain->imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = lveDevice.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void FirstApp::drawFrame() {
    uint32_t imageIndex;
    auto result = lveSwapChain->acquireNextImage(&imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain();
        return;
    }
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    recordCommandBuffer(imageIndex);
    result = lveSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || lveWindow.wasWindowResized()) {
        lveWindow.resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}

void FirstApp::loadModels() {
    std::vector<Engine::Model::Vertex> vertices{
            {{.0f,  -.5f}, {1.0f, .1f,  .1f}},
            {{.5f,  .5f},  {.0f,  .2f,  .5f}},
            {{-.5f, .5f},  {.4f,  1.0f, .0f}}
    };

    model = std::make_unique<Engine::Model>(lveDevice, vertices);
}

void FirstApp::recordCommandBuffer(int imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = lveSwapChain->getRenderPass();
    renderPassInfo.framebuffer = lveSwapChain->getFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = lveSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(lveSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(lveSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, lveSwapChain->getSwapChainExtent()};
    vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

    lvePipeline->bind(commandBuffers[imageIndex]);
    model->bind(commandBuffers[imageIndex]);
    model->draw(commandBuffers[imageIndex]);

    vkCmdEndRenderPass(commandBuffers[imageIndex]);
    if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }

}

void FirstApp::recreateSwapChain() {
    auto extent = lveWindow.getExtent();
    while (extent.width == 0 || extent.height == 0) {
        extent = lveWindow.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(lveDevice.device());

    if (lveSwapChain == nullptr) {
        lveSwapChain = std::make_unique<Engine::SwapChain>(lveDevice, extent);
    } else {
        lveSwapChain = std::make_unique<Engine::SwapChain>(lveDevice, extent, std::move(lveSwapChain));
        if (lveSwapChain->imageCount() != commandBuffers.size()) {
            freeCommandBuffers();
            createCommandBuffers();
        }
    }
    createPipeline();
}

void FirstApp::freeCommandBuffers() {
    vkFreeCommandBuffers(lveDevice.device(), lveDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()),
                         commandBuffers.data());
    commandBuffers.clear();

}
