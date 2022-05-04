//
// Created by Jacopo Beragnoli on 16/04/22.
//

#ifndef MINIMINIMOTORWAYS_FRAMEINFO_H
#define MINIMINIMOTORWAYS_FRAMEINFO_H

#include <vulkan/vulkan_core.h>
#include "Camera.h"
#include "GameObject.h"

namespace Engine {
    // Number of maximum light that can be present in our game object list
    static const uint32_t MAX_LIGHT = 32;

    struct PointLight {
        glm::vec4 position{}; // w is used for padding
        glm::vec4 color{};    // w is intensity
    };

    // Global Uniform Buffer Object that is used when drawing a shader to the screen.
    // https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object
    // https://vulkan-tutorial.com/Uniform_buffers/Descriptor_layout_and_buffer
    struct GlobalUbo {
        glm::mat4 projection{1.f};
        glm::mat4 view{1.f};
        glm::mat4 inverseView{1.f};
        glm::vec4 ambientColor{1.f, 1.f, 1.f, .02f}; // w is light intensity
        PointLight pointLight[MAX_LIGHT];
        int numLights;
    };

    // Contains all information that are needed during a frame draw
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
