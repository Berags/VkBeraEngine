//
// Created by Jacopo Beragnoli on 11/05/22.
//

#ifndef VKBERAENGINE_KEYBOARDINPUTCOMPONENT_H
#define VKBERAENGINE_KEYBOARDINPUTCOMPONENT_H

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "../../engine/Window.h"
#include "../../engine/GameObject.h"
#include "../../engine/FrameInfo.h"
#include "../../engine/ecs/IComponent.h"

namespace Game::Components {
    class KeyboardInputComponent : public Engine::ECS::IComponent {
    public:
        // Struct that handles all key mappings needed for the camera movement
        // it uses GLFW Api
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
            int run = GLFW_KEY_LEFT_SHIFT;
        };

        KeyboardInputComponent(Engine::Window &window, Engine::GameObject &gameObject)
                : window(window),
                  gameObject(gameObject) {}

        void onCreate() override;

        // Changes the camera position based on player input
        // W -> forward
        // S -> backwards
        // A -> left
        // D -> right
        // Arrows -> look around
        void onUpdate(Engine::FrameInfo &frameInfo) override;

        void onDestroy() override;

    private:
        Engine::Window &window;
        Engine::GameObject &gameObject;

        KeyMappings keys{};
        float moveSpeed{3.f};
        const float lookSpeed{3.f};
    };
} // Game::Components

#endif //VKBERAENGINE_KEYBOARDINPUTCOMPONENT_H
