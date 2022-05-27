//
// Created by Jacopo Beragnoli on 25/05/22.
//

#include "../../include/engine/TextureStorage.h"
#include "../../include/engine/Buffer.h"

#include <vulkan/vulkan.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION

#include "../../include/libs/stb_image.h"
#include "../../include/engine/exceptions/vulkan/FailedToCreateVkObject.h"

namespace Engine {
    const std::string TextureStorage::DEFAULT_SAMPLER_NAME = "DefaultSampler";

    TextureStorage::TextureStorage(
            Engine::Device &device)
            : device{device} {
        texturePool = Engine::DescriptorPool::Builder(device)
                .setMaxSets(5)
                .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 5)
                .build();

        textureSetLayout = Engine::DescriptorSetLayout::Builder(device)
                .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
                .build();
    }

    TextureStorage::~TextureStorage() {
        for (auto &kv: textureSamplers) {
            auto &textureSampler = kv.second;
            vkDestroySampler(device.getVkDevice(), textureSampler, nullptr);
        }

        for (auto &kv: textureDatas) {
            auto &textureData = kv.second;
            destroyAndFreeTextureData(textureData);
        }
    }

    const VkDescriptorSet
    TextureStorage::getDescriptorSet(const std::string &textureName, const std::string &samplerName) {
        if (textureDescriptors.count(textureName + samplerName) != 0)
            return textureDescriptors[textureName + samplerName];

        auto descriptorImage = descriptorInfo(samplerName, textureName);

        VkDescriptorSet descriptorSet{};
        Engine::DescriptorWriter(*textureSetLayout, *texturePool)
                .writeImage(0, &descriptorImage)
                .build(descriptorSet);

        textureDescriptors[textureName + samplerName] = descriptorSet;
        return descriptorSet;
    }

    VkDescriptorImageInfo
    TextureStorage::descriptorInfo(const std::string &samplerName, const std::string &textureName) {
        auto &data = getTextureData(textureName);
        auto sampler = getSampler(samplerName);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = data.imageView;
        imageInfo.sampler = sampler;

        return imageInfo;
    }

    VkSampler TextureStorage::getSampler(const std::string &samplerName) {
        if (textureSamplers.count(samplerName) == 0) {
            if (samplerName == DEFAULT_SAMPLER_NAME) {
                VkSamplerCreateInfo defaultSampler{};
                defaultSampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
                defaultSampler.magFilter = VK_FILTER_LINEAR;
                defaultSampler.minFilter = VK_FILTER_LINEAR;
                defaultSampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                defaultSampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                defaultSampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                defaultSampler.anisotropyEnable = VK_TRUE;
                defaultSampler.maxAnisotropy = device.properties.limits.maxSamplerAnisotropy;
                defaultSampler.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
                defaultSampler.unnormalizedCoordinates = VK_FALSE;
                defaultSampler.compareEnable = VK_FALSE;
                defaultSampler.compareOp = VK_COMPARE_OP_ALWAYS;
                defaultSampler.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

                auto textureSampler = createTextureSampler(defaultSampler, samplerName);

                return textureSampler;
            }
        } else {
            return textureSamplers[samplerName];
        }

        throw std::runtime_error("Not find sampler with name:" + samplerName);
    }

    TextureStorage::TextureData &TextureStorage::getTextureData(const std::string &textureName) {
        if (textureDatas.count(textureName) == 0) {
            throw std::runtime_error("Not find texture with name:" + textureName);
        } else {
            return textureDatas[textureName];
        }
    }

    VkSampler TextureStorage::createTextureSampler(
            VkSamplerCreateInfo &samplerInfo,
            const std::string &samplerName
    ) {
        VkSampler textureSampler{};
        if (vkCreateSampler(device.getVkDevice(), &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
            throw Engine::Exceptions::FailedToCreateVkObject("Texture Sampler");
        }

        assert(textureSamplers.count(samplerName) == 0 && "Sampler already in use");
        textureSamplers[samplerName] = textureSampler;

        return textureSampler;
    }

    void TextureStorage::destroySampler(const std::string &samplerName) {
        if (textureSamplers.count(samplerName) == 0)
            return;

        auto &textureSampler = textureSamplers.at(samplerName);
        vkDestroySampler(device.getVkDevice(), textureSampler, nullptr);
        textureDatas.erase(samplerName);
    }

    void TextureStorage::createTextureImage(TextureStorage::TextureData &imageData, const std::string &texturePath) {
        int texWidth, texHeight, texChannels;
        stbi_uc *pixels = stbi_load(texturePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
        VkDeviceSize imageSize = texWidth * texHeight * 4;

        if (!pixels) {
            throw std::runtime_error("failed to load image!");
        }

        Engine::Buffer stagingBuffer{
                device,
                imageSize,
                1,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
        };

        stagingBuffer.map();
        stagingBuffer.writeToBuffer((void *) pixels);
        stbi_image_free(pixels);

        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = texWidth;
        imageInfo.extent.height = texHeight;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        device.createImageWithInfo(
                imageInfo,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                imageData.image,
                imageData.imageMemory
        );
        device.transitionImageLayout(
                imageData.image,
                VK_IMAGE_LAYOUT_UNDEFINED,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
        );

        device.copyBufferToImage(
                stagingBuffer.getVkBuffer(),
                imageData.image,
                static_cast<uint32_t>(texWidth),
                static_cast<uint32_t>(texHeight),
                1
        );

        device.transitionImageLayout(
                imageData.image,
                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        );
    }

    void TextureStorage::loadTexture(const std::string &texturePath, const std::string &textureName) {
        TextureStorage::TextureData imageData{};
        createTextureImage(imageData, texturePath);
        device.createImageView(imageData.imageView, imageData.image, VK_FORMAT_R8G8B8A8_SRGB);

        assert(textureDatas.count(textureName) == 0 && "Texture already in use");
        textureDatas[textureName] = std::move(imageData);
    }

    void TextureStorage::unloadTexture(const std::string &textureName) {
        if (textureDatas.count(textureName) == 0)
            return;

        auto &textureData = textureDatas.at(textureName);
        destroyAndFreeTextureData(textureData);
        textureDatas.erase(textureName);
    }

    void TextureStorage::destroyAndFreeTextureData(const TextureData &data) {
        vkDestroyImageView(device.getVkDevice(), data.imageView, nullptr);
        vkDestroyImage(device.getVkDevice(), data.image, nullptr);
        vkFreeMemory(device.getVkDevice(), data.imageMemory, nullptr);
    }
} // Engine