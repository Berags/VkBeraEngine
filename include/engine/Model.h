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
#include "Buffer.h"
#include "TextureStorage.h"
#include <glm/glm.hpp>
#include <vector>

namespace Engine {
    class Model {
    public:
        struct Vertex {
            // Current 3D world position of the vertex
            glm::vec3 position;

            // Vertex color
            glm::vec3 color;

            // Normalized directional vector intended as a replacement
            //  to the true geometric normal of the getSurface
            // https://en.wikipedia.org/wiki/Vertex_normal
            glm::vec3 normal{};

            // UV mapping is the 3D modeling process of projecting a 2D image
            // to a 3D model's getSurface for texture mapping.
            // https://en.wikipedia.org/wiki/UV_mapping
            glm::vec2 uv{};

            glm::vec2 textCoord{};

            bool operator==(const Vertex &that) const {
                return
                        position == that.position &&
                        color == that.color &&
                        normal == that.normal &&
                        uv == that.uv &&
                        textCoord == that.textCoord;
            }

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        struct Data {
            // All vertices loaded from .obj file
            std::vector<Vertex> vertices{};

            // Stores the indices loaded from .obj file
            // If hasIndexBuffer is false this vector is empty
            std::vector<uint32_t> indices{};

            // Load a model from a file string path
            // Uses https://github.com/tinyobjloader/tinyobjloader library
            // Able to load up to 6M vertices .obj files
            // http://casual-effects.com/data/index.html
            void loadModel(const std::string &filePath);
        };

        Model(Device &device, const Engine::Model::Data &data, std::string &filePath);

        virtual ~Model();

        Model(const Model &) = delete;

        Model &operator=(const Model &) = delete;

        // Factory method that creates a model from a file path
        // Only one model should be created for each game object
        static std::unique_ptr<Engine::Model> createModelFromFile(Engine::Device &device, const char *filePath);

        void bind(VkCommandBuffer commandBuffer);

        void draw(VkCommandBuffer commandBuffer) const;

        [[nodiscard]] const std::string &getFilePath() const;

        void setTextureName(std::string &&texture) {
            this->textureName = std::move(texture);
        }

        std::string &getTextureName() {
            return textureName;
        }

    private:
        Engine::Device &device;

        // The file name
        std::string file;

        std::string textureName;

        std::string samplerName = Engine::TextureStorage::DEFAULT_SAMPLER_NAME;

        // Vertices information
        std::unique_ptr<Engine::Buffer> vertexBuffer;
        uint32_t vertexCount{};

        // Indices information
        std::unique_ptr<Engine::Buffer> indexBuffer;
        uint32_t indexCount{};
        // True if .obj uses an index buffer to optimize the complexity of the model
        bool hasIndexBuffer{false};

        void createVertexBuffers(const std::vector<Vertex> &vertices);

        void createIndexBuffers(const std::vector<uint32_t> &indices);
    };
}

#endif //MINIMINIMOTORWAYS_MODEL_H
