//
// Created by Jacopo Beragnoli on 27/04/22.
//

#ifndef MINIMINIMOTORWAYS_TEXTURE_H
#define MINIMINIMOTORWAYS_TEXTURE_H

#include <vulkan/vulkan_core.h>
#include <memory>
#include "Buffer.h"
#include "Model.h"
#include "Pipeline.h"

namespace Engine {
    class Texture {
    public:
        Texture(std::shared_ptr<Engine::Model> model, Pipeline &pipeline, Engine::Device &device);

        virtual ~Texture();

        void load();

        void
        createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                     VkDeviceMemory &bufferMemory);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void
        createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

        VkCommandBuffer beginSingleTimeCommands();

        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    private:
        std::shared_ptr<Engine::Model> model;
        Engine::Pipeline &pipeline;
        Engine::Device &device;

        VkImage image;
        VkDeviceMemory device_memory;
    };
}


#endif //MINIMINIMOTORWAYS_TEXTURE_H
