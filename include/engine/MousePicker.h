//
// Created by Jacopo Beragnoli on 18/05/22.
//

#ifndef MINIMINIMOTORWAYS_MOUSEPICKER_H
#define MINIMINIMOTORWAYS_MOUSEPICKER_H

#include <glm/glm.hpp>
#include "Window.h"
#include "Camera.h"

namespace Engine::Editor {

    class MousePicker {
    public:
        MousePicker(Engine::Window &window, Engine::Camera &camera, const glm::mat4 &projectionMatrix)
                : window(window), camera(camera), projectionMatrix(projectionMatrix),
                  viewMatrix(camera.getView()), currentRay(glm::vec3(.0f)) {}

        void update();

        [[nodiscard]] const glm::vec3 &getCurrentRay() const { return currentRay; }

    private:
        glm::vec3 currentRay;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        Engine::Window &window;
        Engine::Camera &camera;

        glm::vec3 calculateMouseRay();

        [[nodiscard]] glm::vec2 getNormalizedMouseCoordinates(float mouseX, float mouseY) const;

        [[nodiscard]] glm::vec4 toEyeCoords(const glm::vec4 &clipCoords) const;

        [[nodiscard]] glm::vec3 toWorldCoords(const glm::vec4 &eyeCoords) const;
    };

} // Editor

#endif //MINIMINIMOTORWAYS_MOUSEPICKER_H
