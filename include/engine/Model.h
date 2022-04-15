//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_MODEL_H
#define MINIMINIMOTORWAYS_MODEL_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "Device.h"
#include <glm/glm.hpp>
#include <vector>

namespace Engine {
    class Model {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        struct Data {
            std::vector<Vertex> vertices{};
            std::vector<uint32_t> indices{};
        };

        Model(Device &device, const Engine::Model::Data &data);

        virtual ~Model();

        Model(const Model &) = delete;

        Model &operator=(const Model &) = delete;

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer) const;

    private:
        Engine::Device &device;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        uint32_t indexCount;
        bool hasIndexBuffer{false};

        void createVertexBuffers(const std::vector<Vertex> &vertices);

        void createIndexBuffers(const std::vector<uint32_t> &indices);
    };
}


#endif //MINIMINIMOTORWAYS_MODEL_H
