//
// Created by Jacopo Beragnoli on 07/04/22.
//

#ifndef MINIMINIMOTORWAYS_SWAPCHAIN_H
#define MINIMINIMOTORWAYS_SWAPCHAIN_H

#include "Device.h"
#include <memory>
#include <vulkan/vulkan.h>

namespace Engine {
    class SwapChain {
    public:
        static constexpr int MAX_FRAMES_IN_FLIGHT = 3;

        SwapChain(Device &deviceRef, VkExtent2D windowExtent);

        SwapChain(Device &deviceRef, VkExtent2D windowExtent, std::shared_ptr<SwapChain> previous);

        ~SwapChain();

        SwapChain(const SwapChain &) = delete;

        void operator=(const SwapChain &) = delete;

        VkFramebuffer getFrameBuffer(int index) const { return swapChainFramebuffers[index]; }

        VkRenderPass getRenderPass() const { return renderPass; }

        VkImageView getImageView(int index) const { return swapChainImageViews[index]; }

        size_t imageCount() const { return swapChainImages.size(); }

        VkFormat getSwapChainImageFormat() const { return swapChainImageFormat; }

        VkExtent2D getSwapChainExtent() const { return swapChainExtent; }

        uint32_t width() const { return swapChainExtent.width; }

        uint32_t height() const { return swapChainExtent.height; }

        float extentAspectRatio() const {
            return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
        }

        VkFormat findDepthFormat();

        VkResult acquireNextImage(uint32_t *imageIndex);

        VkResult submitCommandBuffers(const VkCommandBuffer *buffers, const uint32_t *imageIndex);

        bool compareSwapFormats(const Engine::SwapChain &that) const;

    private:
        void init();

        void createSwapChain();

        void createImageViews();

        void createDepthResources();

        void createRenderPass();

        void createFrameBuffers();

        void createSyncObjects();

        // Helper functions
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(
                const std::vector<VkSurfaceFormatKHR> &availableFormats);

        static VkPresentModeKHR chooseSwapPresentMode(
                const std::vector<VkPresentModeKHR> &availablePresentModes);

        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

        VkFormat swapChainImageFormat;
        VkFormat swapChainDepthFormat;
        VkExtent2D swapChainExtent;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkRenderPass renderPass;

        std::vector<VkImage> depthImages;
        std::vector<VkDeviceMemory> depthImageMemorys;
        std::vector<VkImageView> depthImageViews;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        Device &device;
        VkExtent2D windowExtent;

        VkSwapchainKHR swapChain;
        std::shared_ptr<SwapChain> oldSwapChain;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
    };
}

#endif //MINIMINIMOTORWAYS_SWAPCHAIN_H
