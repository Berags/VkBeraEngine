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

        void onCreate() const override {
            std::cout << "Created GameObjectComponent" << std::endl;
        }

        // Changes the camera position based on player input
        // W -> forward
        // S -> backwards
        // A -> left
        // D -> right
        // Arrows -> look around
        void onUpdate(Engine::FrameInfo &frameInfo) override {
            glm::vec3 rotate{0};

            if (glfwGetKey(window.getGlfwWindow(), keys.lookRight) == GLFW_PRESS) rotate.y += 1.f;
            if (glfwGetKey(window.getGlfwWindow(), keys.lookLeft) == GLFW_PRESS) rotate.y -= 1.f;
            if (glfwGetKey(window.getGlfwWindow(), keys.lookUp) == GLFW_PRESS) rotate.x += 1.f;
            if (glfwGetKey(window.getGlfwWindow(), keys.lookDown) == GLFW_PRESS) rotate.x -= 1.f;

            if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon())
                gameObject.transform.rotation += lookSpeed * frameInfo.frameTime * glm::normalize(rotate);

            // Limits pitch values between about +/- 85°
            gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
            gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

            float yaw = gameObject.transform.rotation.y;
            const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
            const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
            const glm::vec3 upDir{0.f, -1.f, 0.f};

            glm::vec3 moveDir{0.f};
            if (glfwGetKey(window.getGlfwWindow(), keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
            if (glfwGetKey(window.getGlfwWindow(), keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
            if (glfwGetKey(window.getGlfwWindow(), keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
            if (glfwGetKey(window.getGlfwWindow(), keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;
            if (glfwGetKey(window.getGlfwWindow(), keys.moveUp) == GLFW_PRESS) moveDir += upDir;
            if (glfwGetKey(window.getGlfwWindow(), keys.moveDown) == GLFW_PRESS) moveDir -= upDir;

            if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
                gameObject.transform.translation += moveSpeed * frameInfo.frameTime * glm::normalize(moveDir);
            }
        }

        void onDestroy() override {
            std::cout << "On destroy method" << std::endl;
        }

    private:
        Engine::Window &window;
        Engine::GameObject &gameObject;

        KeyMappings keys{};
        const float moveSpeed{3.f};
        const float lookSpeed{3.f};
    };
} // Game::Components

#endif //MINIMINIMOTORWAYS_KEYBOARDINPUTCOMPONENT_H
