//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_MODEL_H
#define MINIMINIMOTORWAYS_MODEL_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <unordered_map>

#include "Device.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <vector>


namespace Engine {
    class Model {
    public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;
            glm::vec3 normal{};
            glm::vec2 uv{};

            bool operator==(const Vertex &that) const {
                return position == that.position && color == that.color && normal == that.normal && uv == that.uv;
            }

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        struct Data {
            std::vector<Vertex> vertices{};
            std::vector<uint32_t> indices{};

            void loadModel(const std::string &filePath);
        };

        Model(Device &device, const Engine::Model::Data &data);

        virtual ~Model();

        Model(const Model &) = delete;

        Model &operator=(const Model &) = delete;

        static std::unique_ptr<Engine::Model> createModelFromFile(Engine::Device &device, const std::string &filePath);

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
