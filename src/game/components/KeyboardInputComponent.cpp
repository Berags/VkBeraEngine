//
// Created by Jacopo Beragnoli on 11/05/22.
//

#include "../../../include/game/components/KeyboardInputComponent.h"

namespace Game::Components {
    void KeyboardInputComponent::onCreate() {
        std::cout << "Attached Keyboard Input Controller Component to GameObject with Id: " << gameObject.getId()
                  << std::endl;
    }

    void KeyboardInputComponent::onUpdate(Engine::FrameInfo &frameInfo) {
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
        if (glfwGetKey(window.getGlfwWindow(), keys.run) == GLFW_PRESS) moveSpeed = 5.5f;
        else if (glfwGetKey(window.getGlfwWindow(), keys.run) == GLFW_RELEASE) moveSpeed = 3.5f;

        if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
            gameObject.transform.translation += moveSpeed * frameInfo.frameTime * glm::normalize(moveDir);
        }
    }

    void KeyboardInputComponent::onDestroy() {
        std::cout << "On destroy method" << std::endl;
    }
}