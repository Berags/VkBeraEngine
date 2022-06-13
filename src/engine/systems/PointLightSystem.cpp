//
// Created by Jacopo Beragnoli on 13/04/22.
//

// libs
#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <array>
#include <cassert>
#include <map>

// includes
#include "../../../include/engine/systems/PointLightSystem.h"
#include "../../../include/engine/exceptions/Exception.h"

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
        vkDestroyPipelineLayout(device.getVkDevice(), pipelineLayout, nullptr);
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
        if (vkCreatePipelineLayout(device.getVkDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw Engine::Exceptions::FailedToCreateVkObject("Pipeline Layout");
        }
    }

    void PointLightSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        Engine::Pipeline::defaultConfigInfo(pipelineConfig);
        Engine::Pipeline::enableAlphaRendering(pipelineConfig);
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
        // Sort lights
        std::map<float, Engine::GameObject::id_t> sorted;
        for (auto &kv: frameInfo.gameObjects) {
            auto &obj = kv.second;
            if (!obj.pointLightComponent) continue; // Is not a point light
            // pointLightComponent == nullptr
            // Calculate Distance
            auto offset = frameInfo.camera.getPosition() - obj.transform.translation;
            float distanceSquared = glm::dot(offset, offset);
            sorted[distanceSquared] = obj.getId();
        }

        pipeline->bind(frameInfo.commandBuffer);

        vkCmdBindDescriptorSets(
                frameInfo.commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                pipelineLayout,
                0, 1,
                &frameInfo.globalDescriptorSet,
                0, nullptr);

        // Iterate to sorted map in reverse order
        for (auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
            // Find object with id from sorted map to frameInfo.gameObjects
            auto &gameObj = frameInfo.gameObjects.at(it->second);

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
        auto rotateLight = glm::rotate(glm::mat4(1.f), 0.5f * frameInfo.frameTime, {0.f, -1.f, 0.f});
        int lightIndex = 0;
        for (auto &kv: frameInfo.gameObjects) {
            auto &gameObj = kv.second;
            if (gameObj.pointLightComponent == nullptr) continue;

            // update light position
            gameObj.transform.translation = glm::vec3(rotateLight * glm::vec4(gameObj.transform.translation, 1.f));

            // Copy light to UBO
            ubo.pointLight[lightIndex].position = glm::vec4(gameObj.transform.translation, 1.f);
            ubo.pointLight[lightIndex].color = glm::vec4(gameObj.color, gameObj.pointLightComponent->lightIntensity);
            lightIndex++;
        }

        ubo.numLights = lightIndex;
    }
}