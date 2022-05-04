//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_RENDERSYSTEM_H
#define MINIMINIMOTORWAYS_RENDERSYSTEM_H

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
    class RenderSystem {
    public:
        RenderSystem(Engine::Device &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

        ~RenderSystem();

        RenderSystem(const RenderSystem &) = delete;

        RenderSystem &operator=(const RenderSystem &) = delete;

        void renderGameObjects(Engine::FrameInfo &frameInfo);

        [[nodiscard]] const std::unique_ptr<Engine::Pipeline> &getPipeline() const;

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        Engine::Device &device;
        std::unique_ptr<Engine::Pipeline> pipeline;
        VkPipelineLayout pipelineLayout{};
    };
}


#endif //MINIMINIMOTORWAYS_RENDERSYSTEM_H
