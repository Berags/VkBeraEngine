//
// Created by Jacopo Beragnoli on 27/04/22.
//

#ifndef MINIMINIMOTORWAYS_TEXTURE_H
#define MINIMINIMOTORWAYS_TEXTURE_H

#include <vulkan/vulkan_core.h>
#include <memory>
#include "Buffer.h"
#include "Model.h"
#include "Pipeline.h"

namespace Engine {
    class Texture {
    public:
        struct TextureInfo {
            VkSampler sampler;
            VkImage image;
            VkImageLayout image_layout;
            VkDeviceMemory device_memory;
            VkImageView view;
            uint32_t width, height;
            uint32_t mip_levels;
        } texture;

        Texture(const std::shared_ptr<Engine::Model> &model, Pipeline &pipeline);

        virtual ~Texture();

        void load();

        void destroy(TextureInfo texture);

        void build_command_buffers();

        void draw();

        void generate_quad();

        void setup_descriptor_pool();

        void setup_descriptor_set_layout();

        void setup_descriptor_set();

        void prepare_pipelines();

        void prepare_uniform_buffers();

        void update_uniform_buffers();

    private:
        std::shared_ptr<Engine::Model> model;
        Engine::Pipeline &pipeline;
    };
}


#endif //MINIMINIMOTORWAYS_TEXTURE_H
