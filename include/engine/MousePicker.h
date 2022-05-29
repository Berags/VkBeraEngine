//
// Created by Jacopo Beragnoli on 18/05/22.
//

#ifndef VKBERAENGINE_MOUSEPICKER_H
#define VKBERAENGINE_MOUSEPICKER_H

#include <glm/glm.hpp>
#include "Window.h"
#include "Camera.h"

namespace Engine::Editor {
    // Class that handles all calculation to get RayCasting vector from cursor position
    // Note: In future will be implemented as a reusable component!
    // https://www.youtube.com/watch?v=DLKN0jExRIM
    class MousePicker {
    public:
        MousePicker(Engine::Window &window, Engine::Camera &camera, const glm::mat4 &projectionMatrix)
                : window(window), camera(camera), currentRay(glm::vec3(.0f)) {}

        void update();

        [[nodiscard]] const glm::vec3 &getCurrentRay() const { return currentRay; }

    private:
        // The up-to-date ray casting vector
        glm::vec3 currentRay;

        Engine::Window &window;
        Engine::Camera &camera;

        glm::vec3 calculateMouseRay();

        [[nodiscard]] glm::vec2 getNormalizedMouseCoordinates(float mouseX, float mouseY) const;

        [[nodiscard]] glm::vec4 toEyeCoords(const glm::vec4 &clipCoords) const;

        [[nodiscard]] glm::vec3 toWorldCoords(const glm::vec4 &eyeCoords) const;
    };

} // Editor

#endif //VKBERAENGINE_MOUSEPICKER_H
