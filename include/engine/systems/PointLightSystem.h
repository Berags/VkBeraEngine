//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_POINTLIGHTSYSTEM_H
#define MINIMINIMOTORWAYS_POINTLIGHTSYSTEM_H

#include <memory>
#include <vector>
#include "../Window.h"
#include "../Device.h"
#include "../SwapChain.h"
#include "../Pipeline.h"
#include "../Model.h"
#include "../GameObject.h"
#include "../Renderer.h"
#include "../Camera.h"
#include "../FrameInfo.h"

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


#endif //MINIMINIMOTORWAYS_POINTLIGHTSYSTEM_H
