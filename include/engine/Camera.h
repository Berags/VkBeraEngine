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

        const glm::mat4 &getProjection() const { return projectionMatrix; }

    private:
        glm::mat4 projectionMatrix{1.f};
    };
}


#endif //MINIMINIMOTORWAYS_CAMERA_H
