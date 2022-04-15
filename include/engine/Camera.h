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
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

        void setProspectiveProjection(float fovy, float aspect, float near, float far);

        void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{.0f, -1.f, .0f});

        void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{.0f, -1.f, .0f});
        void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

        const glm::mat4 &getProjection() const;

        const glm::mat4 &getView() const;

    private:
        glm::mat4 projectionMatrix{1.f};
        glm::mat4 viewMatrix{1.f};
    };
}


#endif //MINIMINIMOTORWAYS_CAMERA_H
