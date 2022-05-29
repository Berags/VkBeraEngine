//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef VKBERAENGINE_GAMEOBJECT_H
#define VKBERAENGINE_GAMEOBJECT_H

#include <memory>
#include <unordered_map>
#include <future>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

namespace Engine {
    struct TransformComponent {
        glm::vec3 translation;
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        [[nodiscard]] glm::mat4 mat4() const;

        [[nodiscard]] glm::mat3 normalMatrix() const;
    };

    struct PointLightComponent {
        float lightIntensity = 1.f;
    };

    class GameObject {
    public:
        using id_t = unsigned int;
        using Map = std::unordered_map<id_t, GameObject>;

        // Optional pointers
        std::shared_ptr<Engine::Model> model{};
        std::unique_ptr<PointLightComponent> pointLightComponent = nullptr;

        glm::vec3 color{};
        TransformComponent transform{};
        std::string name;

        GameObject(const GameObject &) = delete;

        GameObject &operator=(const GameObject &) = delete;

        GameObject(GameObject &&) = default;

        GameObject &operator=(GameObject &&) = default;

        [[nodiscard]] id_t getId() const {
            return id;
        }

        // Private Constructor so that a GameObject can be created only by calling factory methods:
        // - createGameObject, to create an actual game object with an .obj model
        // - createPointLight, to create a billboard point light without a model
        explicit GameObject(id_t objectId, const char *name) : id(objectId), name(name) {}

    private:
        // Unique identifier
        id_t id;
    };
}


#endif //VKBERAENGINE_GAMEOBJECT_H
