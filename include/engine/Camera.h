//
// Created by Jacopo Beragnoli on 15/04/22.
//

#ifndef MINIMINIMOTORWAYS_CAMERA_H
#define MINIMINIMOTORWAYS_CAMERA_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

namespace Engine {
    class Camera {
    public:
        // Set camera projection to orthographic
        // http://learnwebgl.brown37.net/08_projections/projections_ortho.html
        // (Unused because is not the correct type of camera in video games as
        // it tends to stretch the view when the aspect ratio is not 4:3)
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

        // Set camera projection to prospective
        // http://faculty.salina.k-state.edu/tim/mVision/ImageFormation/projection.html
        // - fovY is the camera Field of View
        // - aspect is the window current aspect ratio (width/height)
        // - near is the value of the nearest element that should be rendered
        // - far is the value of the farthest element that should be rendered (ie render distance)
        void setProspectiveProjection(float fovY, float aspect, float near, float far);

        void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{.0f, -1.f, .0f});

        void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{.0f, -1.f, .0f});

        void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

        [[nodiscard]] const glm::mat4 &getProjection() const;

        [[nodiscard]] const glm::mat4 &getView() const;

        [[nodiscard]] const glm::mat4 &getInverseViewMatrix() const;

        [[nodiscard]] const glm::vec3 getPosition() const;

    private:
        glm::mat4 projectionMatrix{1.f};
        glm::mat4 viewMatrix{1.f};
        glm::mat4 inverseViewMatrix{1.f};
    };
}


#endif //MINIMINIMOTORWAYS_CAMERA_H
