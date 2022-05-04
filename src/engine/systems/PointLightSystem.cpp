//
// Created by Jacopo Beragnoli on 13/04/22.
//

// libs
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <array>
#include <cassert>

// includes
#include "../../../include/engine/systems/PointLightSystem.h"
#include "../../../include/engine/exceptions/vulkan/FailedToCreatePipeLineLayoutException.h"

namespace Engine {

    struct PointLightPushConstants {
        glm::vec4 position{};
        glm::vec4 color{};
        float radius;
    };

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
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(PointLightPushConstants);

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts{globalSetLayout};

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
        pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
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

        for (auto &kv: frameInfo.gameObjects) {
            auto &gameObj = kv.second;
            if (gameObj.pointLightComponent == nullptr) continue;

            PointLightPushConstants push{};
            push.position = glm::vec4(gameObj.transform.translation, 1.f);
            push.color = glm::vec4(gameObj.color, gameObj.pointLightComponent->lightIntensity);
            push.radius = gameObj.transform.scale.x;
            vkCmdPushConstants(frameInfo.commandBuffer,
                               pipelineLayout,
                               VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                               0,
                               sizeof(PointLightPushConstants),
                               &push);
            vkCmdDraw(frameInfo.commandBuffer, 6, 1, 0, 0);
        }
    }

    void PointLightSystem::update(FrameInfo &frameInfo, GlobalUbo &ubo) {
        int lightIndex = 0;
        for (auto &kv: frameInfo.gameObjects) {
            auto &gameObj = kv.second;
            if (gameObj.pointLightComponent == nullptr) continue;

            // Copy light to UBO
            ubo.pointLight[lightIndex].position = glm::vec4(gameObj.transform.translation, 1.f);
            ubo.pointLight[lightIndex].color = glm::vec4(gameObj.color, gameObj.pointLightComponent->lightIntensity);
            lightIndex++;
        }

        ubo.numLights = lightIndex;
    }
}