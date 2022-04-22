//
// Created by Jacopo Beragnoli on 17/04/22.
//

#ifndef MINIMINIMOTORWAYS_DESCRIPTORSETLAYOUT_H
#define MINIMINIMOTORWAYS_DESCRIPTORSETLAYOUT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Device.h"

namespace Engine {
    class DescriptorSetLayout {
    public:
        class Builder {
        public:
            Builder(Engine::Device &device) : device{device} {}

            Builder &addBinding(
                    uint32_t binding,
                    VkDescriptorType descriptorType,
                    VkShaderStageFlags stageFlags,
                    uint32_t count = 1);

            std::unique_ptr<DescriptorSetLayout> build() const;

        private:
            Engine::Device &device;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };

        DescriptorSetLayout(
                Engine::Device
                &device,
                std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings
        );

        ~DescriptorSetLayout();

        DescriptorSetLayout(const DescriptorSetLayout &) = delete;

        DescriptorSetLayout &operator=(const DescriptorSetLayout &) = delete;

        [[nodiscard]] VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;
    private:
        Engine::Device &device;
        VkDescriptorSetLayout descriptorSetLayout;

        friend class LveDescriptorWriter;
    };

    class DescriptorPool {
    public:
        class Builder {
        public:
            Builder(Engine::Device &device) : device{device} {}

            Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);

            Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);

            Builder &setMaxSets(uint32_t count);

            [[nodiscard]] std::unique_ptr<DescriptorPool> build() const;

        private:
            Engine::Device &device;
            std::vector<VkDescriptorPoolSize> poolSizes{};
            uint32_t maxSets = 1000;
            VkDescriptorPoolCreateFlags poolFlags = 0;
        };

        DescriptorPool(
                Engine::Device &device,
                uint32_t maxSets,
                VkDescriptorPoolCreateFlags poolFlags,
                const std::vector<VkDescriptorPoolSize> &poolSizes);

        ~DescriptorPool();

        DescriptorPool(const DescriptorPool &) = delete;

        DescriptorPool &operator=(const DescriptorPool &) = delete;

        bool allocateDescriptor(
                VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;

        void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;

        void resetPool();

        Engine::Device &device;
    private:
        VkDescriptorPool descriptorPool;

        friend class LveDescriptorWriter;
    };

    class DescriptorWriter {
    public:
        DescriptorWriter(DescriptorSetLayout &setLayout, DescriptorPool &pool);

        DescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);

        DescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

        bool build(VkDescriptorSet &set);

        void overwrite(VkDescriptorSet &set);

    private:
        DescriptorSetLayout &setLayout;
        DescriptorPool &pool;
        std::vector<VkWriteDescriptorSet> writes;
    };
}
#endif //MINIMINIMOTORWAYS_DESCRIPTORSETLAYOUT_H
