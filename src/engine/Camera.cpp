//
// Created by Jacopo Beragnoli on 15/04/22.
//

#include "../../include/engine/Camera.h"
#include <cassert>
#include <limits>

namespace Engine {

    void Camera::setOrthographicProjection(float left, float right, float top, float bottom, float near, float far) {
        projectionMatrix = glm::mat4{1.0f};
        projectionMatrix[0][0] = 2.f / (right - left);
        projectionMatrix[1][1] = 2.f / (bottom - top);
        projectionMatrix[2][2] = 1.f / (far - near);
        projectionMatrix[3][0] = -(right + left) / (right - left);
        projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
        projectionMatrix[3][2] = -near / (far - near);
    }

    /**
     *
     * @param fovY
     * @param aspect
     * @param near
     * @param far The distance that the camera will render
     */
    void Camera::setProspectiveProjection(float fovY, float aspect, float near, float far) {
        assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
        const float tanHalfFovY = tan(fovY / 2.f);
        projectionMatrix = glm::mat4{0.0f};
        projectionMatrix[0][0] = 1.f / (aspect * tanHalfFovY);
        projectionMatrix[1][1] = 1.f / (tanHalfFovY);
        projectionMatrix[2][2] = far / (far - near);
        projectionMatrix[2][3] = 1.f;
        projectionMatrix[3][2] = -(far * near) / (far - near);
    }

    const glm::mat4 &Camera::getProjection() const { return projectionMatrix; }

    const glm::mat4 &Camera::getView() const { return viewMatrix; }

    void Camera::setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
        // Constructing and orthonormal basis
        const glm::vec3 i{glm::normalize(direction)};
        const glm::vec3 j{glm::normalize(glm::cross(i, up))};
        const glm::vec3 k{glm::cross(i, j)};

        viewMatrix = glm::mat4{1.f};
        viewMatrix[0][0] = j.x;
        viewMatrix[1][0] = j.y;
        viewMatrix[2][0] = j.z;
        viewMatrix[0][1] = k.x;
        viewMatrix[1][1] = k.y;
        viewMatrix[2][1] = k.z;
        viewMatrix[0][2] = i.x;
        viewMatrix[1][2] = i.y;
        viewMatrix[2][2] = i.z;
        viewMatrix[3][0] = -glm::dot(j, position);
        viewMatrix[3][1] = -glm::dot(k, position);
        viewMatrix[3][2] = -glm::dot(i, position);
    }

    void Camera::setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
        setViewDirection(position, target - position, up);
    }

    void Camera::setViewYXZ(glm::vec3 position, glm::vec3 rotation) {
        // Constructing the inverse of rotation matrix
        // R^-1 = R^T
        // The inverse of rotation matrix is just its transpose
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);
        const glm::vec3 u{(c1 * c3 + s1 * s2 * s3), (c2 * s3), (c1 * s2 * s3 - c3 * s1)};
        const glm::vec3 v{(c3 * s1 * s2 - c1 * s3), (c2 * c3), (c1 * c3 * s2 + s1 * s3)};
        const glm::vec3 w{(c2 * s1), (-s2), (c1 * c2)};
        viewMatrix = glm::mat4{1.f};
        viewMatrix[0][0] = u.x;
        viewMatrix[1][0] = u.y;
        viewMatrix[2][0] = u.z;
        viewMatrix[0][1] = v.x;
        viewMatrix[1][1] = v.y;
        viewMatrix[2][1] = v.z;
        viewMatrix[0][2] = w.x;
        viewMatrix[1][2] = w.y;
        viewMatrix[2][2] = w.z;
        viewMatrix[3][0] = -glm::dot(u, position);
        viewMatrix[3][1] = -glm::dot(v, position);
        viewMatrix[3][2] = -glm::dot(w, position);
    }
}