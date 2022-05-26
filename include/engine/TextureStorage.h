//
// Created by Jacopo Beragnoli on 25/05/22.
//

#ifndef MINIMINIMOTORWAYS_TEXTURESTORAGE_H
#define MINIMINIMOTORWAYS_TEXTURESTORAGE_H

#include <string>
#include <unordered_map>

#include "Device.h"
#include "Descriptors.h"

namespace Engine {
    class TextureStorage {
    public:
        static const std::string DEFAULT_SAMPLER_NAME;

        struct TextureData {
            VkImage image;
            VkImageView imageView;
            VkDeviceMemory imageMemory;
        };

        explicit TextureStorage(Engine::Device &device);

        ~TextureStorage();

        TextureStorage(const TextureStorage &) = delete;

        TextureStorage &operator=(const TextureStorage &) = delete;

        void loadTexture(const std::string &texturePath, const std::string &textureName);

        void unloadTexture(const std::string &textureName);

        VkSampler createTextureSampler(VkSamplerCreateInfo &samplerInfo, const std::string &samplerName);

        void destroySampler(const std::string &samplerName);

        const Engine::DescriptorSetLayout &getTextureDescriptorSetLayout() const { return *textureSetLayout; }

        const VkDescriptorSet getDescriptorSet(const std::string &textureName, const std::string &samplerName);

        VkDescriptorImageInfo descriptorInfo(const std::string &samplerName, const std::string &textureName);

    private:
        void createTextureImage(TextureStorage::TextureData &imageData, const std::string &texturePath);

        void destroyAndFreeTextureData(const TextureData &data);

        TextureData &getTextureData(const std::string &textureName);

        VkSampler getSampler(const std::string &samplerName);


        std::unordered_map<std::string, TextureData> textureDatas;
        std::unordered_map<std::string, VkSampler> textureSamplers;
        std::unique_ptr<Engine::DescriptorPool> texturePool;
        std::unique_ptr<Engine::DescriptorSetLayout> textureSetLayout;
        std::unordered_map<std::string, VkDescriptorSet> textureDescriptors;

        Engine::Device &device;
    };

} // Engine

#endif //MINIMINIMOTORWAYS_TEXTURESTORAGE_H
