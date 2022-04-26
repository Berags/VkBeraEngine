//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_GAMEOBJECT_H
#define MINIMINIMOTORWAYS_GAMEOBJECT_H

#include <memory>
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

    class GameObject {
    public:
        using id_t = unsigned int;
        std::shared_ptr<Engine::Model> model{};
        glm::vec3 color{};
        TransformComponent transform{};

        static GameObject createGameObject(std::string &name) {
            static id_t currentId = 0;
            return GameObject{currentId++, name};
        }

        GameObject(const GameObject &) = delete;

        GameObject &operator=(const GameObject &) = delete;

        GameObject(GameObject &&) = default;

        GameObject &operator=(GameObject &&) = default;

        [[nodiscard]] id_t getId() const {
            return id;
        }

        [[nodiscard]] const std::string &getName() const {
            return name;
        }

    private:
        id_t id;

        std::string name;

        explicit GameObject(id_t objectId, std::string &name) : id(objectId), name(name) {}
    };
}


#endif //MINIMINIMOTORWAYS_GAMEOBJECT_H
