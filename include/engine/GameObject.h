//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_GAMEOBJECT_H
#define MINIMINIMOTORWAYS_GAMEOBJECT_H

#include <memory>
#include <glm/glm.hpp>
#include "Model.h"

namespace Engine {
    struct Transform2dComponent {
        glm::vec2 translation;
        glm::vec2 scale{1.f, 1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix{{c,  s},
                                {-s, c}};

            glm::mat2 scaleMat{{scale.x, .0f},
                               {.0f,     scale.y}};
            return rotMatrix * scaleMat;
        }
    };

    class GameObject {
    public:
        using id_t = unsigned int;
        std::shared_ptr<Engine::Model> model{};
        glm::vec3 color{};
        Transform2dComponent transform2D{};

        static GameObject createGameObject() {
            static id_t currentId = 0;
            return GameObject{currentId++};
        }

        GameObject(const GameObject &) = delete;

        GameObject &operator=(const GameObject &) = delete;

        GameObject(GameObject &&) = default;

        GameObject &operator=(GameObject &&) = default;

        id_t getId() const {
            return id;
        }

    private:
        id_t id;

        GameObject(id_t objectId) : id(objectId) {}
    };
}


#endif //MINIMINIMOTORWAYS_GAMEOBJECT_H
