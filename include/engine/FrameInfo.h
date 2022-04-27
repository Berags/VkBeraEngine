//
// Created by Jacopo Beragnoli on 16/04/22.
//

#ifndef MINIMINIMOTORWAYS_FRAMEINFO_H
#define MINIMINIMOTORWAYS_FRAMEINFO_H

#include <vulkan/vulkan_core.h>
#include "Camera.h"
#include "GameObject.h"

namespace Engine {
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
