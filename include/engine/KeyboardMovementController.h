//
// Created by Jacopo Beragnoli on 15/04/22.
//

#ifndef MINIMINIMOTORWAYS_KEYBOARDMOVEMENTCONTROLLER_H
#define MINIMINIMOTORWAYS_KEYBOARDMOVEMENTCONTROLLER_H

#include <GLFW/glfw3.h>
#include "GameObject.h"

namespace Engine {
    class KeyboardMovementController {
    public:
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

        void moveInPlaneXZ(GLFWwindow *glfWwindow, float dt, Engine::GameObject &gameObject) const;

        KeyMappings keys{};
        float moveSpeed{3.f};
        float lookSpeed{1.5f};
    private:
    };
}


#endif //MINIMINIMOTORWAYS_KEYBOARDMOVEMENTCONTROLLER_H
