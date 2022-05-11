//
// Created by Jacopo Beragnoli on 11/05/22.
//

#ifndef MINIMINIMOTORWAYS_KEYBOARDINPUTCOMPONENT_H
#define MINIMINIMOTORWAYS_KEYBOARDINPUTCOMPONENT_H

#include "../../engine/Core.h"

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
        };

        KeyboardInputComponent(Engine::Window &window, Engine::GameObject &gameObject)
                : window(window),
                  gameObject(gameObject) {}

        void onCreate() const override;

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
        const float moveSpeed{3.f};
        const float lookSpeed{3.f};
    };
} // Game::Components

#endif //MINIMINIMOTORWAYS_KEYBOARDINPUTCOMPONENT_H
