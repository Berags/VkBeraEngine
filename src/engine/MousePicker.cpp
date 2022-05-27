//
// Created by Jacopo Beragnoli on 18/05/22.
//

#include "../../include/engine/MousePicker.h"

namespace Engine::Editor {
    glm::vec3 MousePicker::calculateMouseRay() {
        float mouseX = window.getMouseX();
        float mouseY = window.getMouseY();

        glm::vec2 normalizedMouseCoordinates = getNormalizedMouseCoordinates(mouseX, mouseY);
        glm::vec4 clipCoords = glm::vec4(normalizedMouseCoordinates, -1.f, 1.f);
        glm::vec4 eyeCoords = toEyeCoords(clipCoords);
        glm::vec3 worldRay = toWorldCoords(eyeCoords);

        return worldRay;
    }

    void MousePicker::update() {
        currentRay = calculateMouseRay();
    }

    glm::vec2 MousePicker::getNormalizedMouseCoordinates(float mouseX, float mouseY) const {
        float x = (2.f * mouseX) / window.getWidth() - 1.f;
        float y = (2.f * mouseY) / window.getHeight() - 1.f;
        return glm::vec2(x, -y);
    }

    glm::vec4 MousePicker::toEyeCoords(const glm::vec4 &clipCoords) const {
        glm::vec4 eyeCoords = glm::inverse(camera.getProjection()) * clipCoords;
        return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, .0f);
    }

    glm::vec3 MousePicker::toWorldCoords(const glm::vec4 &eyeCoords) const {
        return glm::vec3(glm::normalize(camera.getInverseViewMatrix() * eyeCoords));
    }
} // Engine::Editor