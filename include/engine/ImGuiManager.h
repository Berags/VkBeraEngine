//
// Created by Jacopo Beragnoli on 26/04/22.
//

#ifndef MINIMINIMOTORWAYS_IMGUIMANAGER_H
#define MINIMINIMOTORWAYS_IMGUIMANAGER_H

#include <vulkan/vulkan_core.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "Window.h"
#include "Device.h"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_vulkan.h"
#include "Core.h"

namespace Engine {
    static void check_vk_result(VkResult err) {
        if (err == 0) return;
        fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (err < 0) abort();
    }

    class ImGuiManager {
    public:
        ImGuiManager(Engine::Window &window,
                     Engine::Device &device,
                     VkRenderPass renderPass,
                     uint32_t imageCount
        );

        ~ImGuiManager();

        void newFrame();

        void render(VkCommandBuffer commandBuffer);

        void run(Engine::FrameInfo &frameInfo);

        // ImGui Windows states
        bool showDemoWindow = false;
        bool showGameObjectsWindow = false;
        bool showAddEntityWindow = false;

    private:
        Engine::Device &device;

        VkDescriptorPool descriptorPool;

        static void ShowExampleAppSimpleOverlay(bool *p_open);

        static void saveObjectToJson(GameObject &obj, json &j);

        static void showGameObject(FrameInfo &frameInfo,
                                   Engine::GameObject::Map::iterator &iterator,
                                   GameObject &gameObj);

        static void showLightEditor(FrameInfo &frameInfo,
                                    Engine::GameObject::Map::iterator &iterator,
                                    GameObject &gameObj);

        static void showEntityEditor(FrameInfo &frameInfo,
                                     Engine::GameObject::Map::iterator &iterator,
                                     GameObject &gameObj);
    };
};


#endif //MINIMINIMOTORWAYS_IMGUIMANAGER_H
