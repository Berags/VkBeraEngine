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
#include "GameObject.h"
#include "FrameInfo.h"

namespace Engine {
    static void check_vk_result(VkResult err) {
        if (err == 0) return;
        fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
        if (err < 0) abort();
    }

    class ImGuiManager {
    public:
        ImGuiManager(Engine::Window
                     &window,
                     Engine::Device &device, VkRenderPass
                     renderPass,
                     uint32_t imageCount
        );

        ~ImGuiManager();

        void newFrame();

        void render(VkCommandBuffer commandBuffer);

        // Example state
        bool show_demo_window = false;
        bool showGameObjectsWindow = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        void run(Engine::FrameInfo &frameInfo);

    private:
        Engine::Device &device;

        VkDescriptorPool descriptorPool;

        static void ShowExampleAppSimpleOverlay(bool *p_open);

        void saveObjectToJson(GameObject &obj, json &j);
    };
};


#endif //MINIMINIMOTORWAYS_IMGUIMANAGER_H
