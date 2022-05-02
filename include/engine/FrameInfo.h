//
// Created by Jacopo Beragnoli on 16/04/22.
//

#ifndef MINIMINIMOTORWAYS_FRAMEINFO_H
#define MINIMINIMOTORWAYS_FRAMEINFO_H

#include <vulkan/vulkan_core.h>
#include "Camera.h"
#include "GameObject.h"

namespace Engine {
    static const uint8_t MAX_LIGHT = 10;

    struct PointLight {
        glm::vec4 position{}; // w is padding
        glm::vec4 color{};    // w is intensity
    };

    struct GlobalUbo {
        glm::mat4 projection{1.f};
        glm::mat4 view{1.f};
        glm::mat4 inverseView{1.f};
        glm::vec4 ambientColor{1.f, 1.f, 1.f, .02f}; // w is light intensity
        PointLight pointLight[MAX_LIGHT];
        int numLights;
    };

    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        Engine::Camera &camera;
        VkDescriptorSet globalDescriptorSet;
        Engine::GameObject::Map &gameObjects;
    };
}

#endif //MINIMINIMOTORWAYS_FRAMEINFO_H
