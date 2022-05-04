//
// Created by Jacopo Beragnoli on 15/04/22.
//

// libs
#include <limits>

// includes
#include "../../include/engine/KeyboardMovementController.h"

namespace Engine {

    void KeyboardMovementController::moveInPlaneXZ(GLFWwindow *glfWwindow, float dt, GameObject &gameObject) const {
        glm::vec3 rotate{0};

        if (glfwGetKey(glfWwindow, keys.lookRight) == GLFW_PRESS) rotate.y += 1.f;
        if (glfwGetKey(glfWwindow, keys.lookLeft) == GLFW_PRESS) rotate.y -= 1.f;
        if (glfwGetKey(glfWwindow, keys.lookUp) == GLFW_PRESS) rotate.x += 1.f;
        if (glfwGetKey(glfWwindow, keys.lookDown) == GLFW_PRESS) rotate.x -= 1.f;

        if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon())
            gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);

        // Limits pitch values between about +/- 85°
        gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
        gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

        float yaw = gameObject.transform.rotation.y;
        const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
        const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
        const glm::vec3 upDir{0.f, -1.f, 0.f};

        glm::vec3 moveDir{0.f};
        if (glfwGetKey(glfWwindow, keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
        if (glfwGetKey(glfWwindow, keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
        if (glfwGetKey(glfWwindow, keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
        if (glfwGetKey(glfWwindow, keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;
        if (glfwGetKey(glfWwindow, keys.moveUp) == GLFW_PRESS) moveDir += upDir;
        if (glfwGetKey(glfWwindow, keys.moveDown) == GLFW_PRESS) moveDir -= upDir;

        if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
            gameObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
        }
    }
}