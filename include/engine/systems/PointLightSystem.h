//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef VKBERAENGINE_POINTLIGHTSYSTEM_H
#define VKBERAENGINE_POINTLIGHTSYSTEM_H

#include <memory>
#include <vector>
#include "../FrameInfo.h"
#include "../Pipeline.h"

namespace Engine {
    class PointLightSystem {
    public:
        PointLightSystem(Engine::Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

        ~PointLightSystem();

        PointLightSystem(const PointLightSystem &) = delete;

        PointLightSystem &operator=(const PointLightSystem &) = delete;

        void render(Engine::FrameInfo &frameInfo);

        void update(Engine::FrameInfo &frameInfo, GlobalUbo &ubo);

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        Engine::Device &device;
        std::unique_ptr<Engine::Pipeline> pipeline;
        VkPipelineLayout pipelineLayout{};
    };
}


#endif //VKBERAENGINE_POINTLIGHTSYSTEM_H
