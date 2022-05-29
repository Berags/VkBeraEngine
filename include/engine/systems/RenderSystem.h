//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef VKBERAENGINE_RENDERSYSTEM_H
#define VKBERAENGINE_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include "../FrameInfo.h"
#include "../Pipeline.h"
#include "../Descriptors.h"

namespace Engine {
    class RenderSystem {
    public:
        RenderSystem(
                Engine::Device &device,
                Engine::TextureStorage &lveTextureStorage,
                VkRenderPass renderPass,
                Engine::DescriptorSetLayout &globalSetLayout
        );

        ~RenderSystem();

        RenderSystem(const RenderSystem &) = delete;

        RenderSystem &operator=(const RenderSystem &) = delete;

        void renderGameObjects(Engine::FrameInfo &frameInfo);

        [[nodiscard]] const std::unique_ptr<Engine::Pipeline> &getPipeline() const;

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        Engine::Device &device;
        Engine::TextureStorage &textureStorage;

        std::unique_ptr<Engine::Pipeline> pipeline;
        VkPipelineLayout pipelineLayout{};
    };
}


#endif //VKBERAENGINE_RENDERSYSTEM_H
