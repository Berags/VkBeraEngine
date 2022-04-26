//
// Created by Jacopo Beragnoli on 26/04/22.
//

#ifndef MINIMINIMOTORWAYS_IMGUIMANAGER_H
#define MINIMINIMOTORWAYS_IMGUIMANAGER_H

#include <vulkan/vulkan_core.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "Window.h"
#include "Device.h"

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glfw.h"
#include "../libs/imgui/imgui_impl_vulkan.h"

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
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        void runExample();

    private:
        Engine::Device &device;

        // We haven't yet covered descriptor pools in the tutorial series
        // so I'm just going to create one for just imgui and store it here for now.
        // maybe its preferred to have a separate descriptor pool for imgui anyway,
        // I haven't looked into imgui best practices at all.
        VkDescriptorPool descriptorPool;
    };
};


#endif //MINIMINIMOTORWAYS_IMGUIMANAGER_H
