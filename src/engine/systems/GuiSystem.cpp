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
#include "../../../include/engine/systems/GuiSystem.h"
#include "../../../include/engine/exceptions/Exception.h"

namespace Engine {
    struct SimplePushConstantData {
        glm::mat4 transform{1.f};
        alignas(16) glm::vec3 color{};
    };

    GuiSystem::GuiSystem(Engine::Device &device,
                         Engine::TextureStorage &lveTextureStorage,
                         VkRenderPass renderPass,
                         Engine::DescriptorSetLayout &globalSetLayout) :
            device{device}, textureStorage{lveTextureStorage},
            crosshair(GameObjectFactory::createGameObject("Crosshair")) {
        createPipelineLayout(globalSetLayout.getDescriptorSetLayout());
        createPipeline(renderPass);

        crosshair.model = Engine::Model::createModelFromFile(device, "../models/quad.obj");
    }

    GuiSystem::~GuiSystem() {
        vkDestroyPipelineLayout(device.getVkDevice(), pipelineLayout, nullptr);
    }

    void GuiSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        std::vector<VkDescriptorSetLayout> descriptorSetLayouts{
                globalSetLayout,
                textureStorage.getTextureDescriptorSetLayout().getDescriptorSetLayout()
        };

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
        pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(device.getVkDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw Engine::Exceptions::FailedToCreateVkObject("Pipeline Layout");
        }
    }

    void GuiSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        Engine::Pipeline::defaultConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Engine::Pipeline>(
                device,
                "../shaders/gui_shader.vert.spv",
                "../shaders/gui_shader.frag.spv",
                pipelineConfig);
    }

    void GuiSystem::render(
            Engine::FrameInfo &frameInfo) {
        pipeline->bind(frameInfo.commandBuffer);

        vkCmdBindDescriptorSets(
                frameInfo.commandBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                pipelineLayout,
                0,
                1,
                &frameInfo.globalDescriptorSet,
                0,
                nullptr
        );

        SimplePushConstantData push{};
        push.color = crosshair.color;
        push.transform = crosshair.transform.normalMatrix();

        vkCmdPushConstants(
                frameInfo.commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push
        );

        crosshair.model->bind(frameInfo.commandBuffer);
        crosshair.model->draw(frameInfo.commandBuffer);
    }

    const std::unique_ptr<Engine::Pipeline> &GuiSystem::getPipeline() const {
        return pipeline;
    }
}