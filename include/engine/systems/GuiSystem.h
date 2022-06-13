//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef VKBERAENGINE_GUISYSTEM_H
#define VKBERAENGINE_GUISYSTEM_H

#include <memory>
#include <vector>
#include "../FrameInfo.h"
#include "../Pipeline.h"
#include "../Descriptors.h"
#include "../GameObjectFactory.h"

namespace Engine {
    class GuiSystem {
    public:
        GuiSystem(
                Engine::Device &device,
                Engine::TextureStorage &lveTextureStorage,
                VkRenderPass renderPass,
                Engine::DescriptorSetLayout &globalSetLayout
        );

        ~GuiSystem();

        GuiSystem(const GuiSystem &) = delete;

        GuiSystem &operator=(const GuiSystem &) = delete;

        void render(Engine::FrameInfo &frameInfo);

        [[nodiscard]] const std::unique_ptr<Engine::Pipeline> &getPipeline() const;

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);

        Engine::Device &device;
        Engine::TextureStorage &textureStorage;

        Engine::GameObject crosshair;

        std::unique_ptr<Engine::Pipeline> pipeline;
        VkPipelineLayout pipelineLayout{};
    };
}


#endif //VKBERAENGINE_GUISYSTEM_H
