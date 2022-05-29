//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef VKBERAENGINE_RENDERER_H
#define VKBERAENGINE_RENDERER_H

#include <memory>
#include <vector>
#include <cassert>
#include "Window.h"
#include "Device.h"
#include "SwapChain.h"

namespace Engine {
    class Renderer {
    public:
        Renderer(Engine::Window &window,
                 Engine::Device &lveDevice);

        ~Renderer();

        Renderer(const Renderer &) = delete;

        Renderer &operator=(const Renderer &) = delete;

        VkCommandBuffer beginFrame();

        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        void endSwapChainRenderPass(VkCommandBuffer commandBuffer) const;

        [[nodiscard]] VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }

        [[nodiscard]] float getAspectRatio() const { return swapChain->extentAspectRatio(); }

        [[nodiscard]] bool isFrameInProgress() const { return isFrameStarted; }

        [[nodiscard]] uint32_t getImageCount() const { return swapChain->imageCount(); }

        [[nodiscard]] VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        [[nodiscard]] int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

    private:
        void createCommandBuffers();

        void freeCommandBuffers();

        void recreateSwapChain();

        Engine::Window &window;
        Engine::Device &device;
        std::unique_ptr<Engine::SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
    };
}


#endif //VKBERAENGINE_RENDERER_H
