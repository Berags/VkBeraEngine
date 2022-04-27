//
// Created by Jacopo Beragnoli on 13/04/22.
//

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <array>
#include <cassert>

// headers
#include "../../../include/engine/systems/PointLightSystem.h"
#include "../../../include/engine/exceptions/vulkan/FailedToCreatePipeLineLayoutException.h"

namespace Engine {

    PointLightSystem::PointLightSystem(Engine::Device &device, VkRenderPass renderPass,
                                       VkDescriptorSetLayout globalSetLayout)
            : device(device) {
        createPipelineLayout(globalSetLayout);
        createPipeline(renderPass);
    }

    PointLightSystem::~PointLightSystem() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
    }

    void PointLightSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
        // VkPushConstantRange pushConstantRange{};
        // pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        // pushConstantRange.offset = 0;
        // pushConstantRange.size = sizeof(SimplePushConstantData);

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
        pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw Engine::Exceptions::FailedToCreatePipeLineLayoutException();
        }
    }

    void PointLightSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        Engine::Pipeline::defaultConfigInfo(pipelineConfig);
        pipelineConfig.attributeDescription.clear();
        pipelineConfig.bindingDescription.clear();
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Engine::Pipeline>(
                device,
                "../shaders/point_light.vert.spv",
                "../shaders/point_light.frag.spv",
                pipelineConfig);
    }

    void PointLightSystem::render(
            Engine::FrameInfo &frameInfo) {
        pipeline->bind(frameInfo.commandBuffer);

        vkCmdBindDescriptorSets(
                frameInfo.commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                pipelineLayout,
                0, 1,
                &frameInfo.globalDescriptorSet,
                0, nullptr);

        vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
    }
}