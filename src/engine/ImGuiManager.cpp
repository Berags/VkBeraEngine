//
// Created by Jacopo Beragnoli on 26/04/22.
//

#include "../../include/engine/ImGuiManager.h"
#include <vulkan/vulkan_core.h>
#include <stdexcept>
#include "../../include/engine/Window.h"
#include "../../include/engine/Device.h"
#include "../../include/engine/FrameInfo.h"

namespace Engine {
    ImGuiManager::ImGuiManager(
            Engine::Window &window, Engine::Device &device, VkRenderPass renderPass, uint32_t imageCount)
            : device{device} {
        // set up a descriptor pool stored on this instance, see header for more comments on this.
        VkDescriptorPoolSize pool_sizes[] = {
                {VK_DESCRIPTOR_TYPE_SAMPLER,                1000},
                {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
                {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000},
                {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000},
                {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000},
                {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000},
                {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000},
                {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000},
                {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
                {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
                {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000}};
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t) IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        if (vkCreateDescriptorPool(device.device(), &pool_info, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up descriptor pool for imgui");
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        // Initialize imgui for vulkan
        ImGui_ImplGlfw_InitForVulkan(window.getGlfwWindow(), true);
        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = device.getInstance();
        init_info.PhysicalDevice = device.getPhysicalDevice();
        init_info.Device = device.device();
        init_info.QueueFamily = device.getGraphicsQueueFamily();
        init_info.Queue = device.graphicsQueue();

        // pipeline cache is a potential future optimization, ignoring for now
        init_info.PipelineCache = VK_NULL_HANDLE;
        init_info.DescriptorPool = descriptorPool;
        // todo, I should probably get around to integrating a memory allocator library such as Vulkan
        // memory allocator (VMA) sooner than later. We don't want to have to update adding an allocator
        // in a ton of locations.
        init_info.Allocator = VK_NULL_HANDLE;
        init_info.MinImageCount = 2;
        init_info.ImageCount = imageCount;
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info, renderPass);

        // upload fonts, this is done by recording and submitting a one time use command buffer
        // which can be done easily bye using some existing helper functions on the lve device object
        auto commandBuffer = device.beginSingleTimeCommands();
        ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
        device.endSingleTimeCommands(commandBuffer);
        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    ImGuiManager::~ImGuiManager() {
        vkDestroyDescriptorPool(device.device(), descriptorPool, nullptr);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiManager::newFrame() {
        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    // this tells imgui that we're done setting up the current frame,
    // then gets the draw data from imgui and uses it to record to the provided
    // command buffer the necessary draw commands
    void ImGuiManager::render(VkCommandBuffer commandBuffer) {
        ImGui::Render();
        ImDrawData *drawdata = ImGui::GetDrawData();
        ImGui_ImplVulkan_RenderDrawData(drawdata, commandBuffer);
    }

    void ImGuiManager::run(Engine::FrameInfo &frameInfo) {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can
        // browse its code to learn more about Dear ImGui!).
        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named
        // window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("VkBeraEngine - Debug");  // Create a window called "Hello, world!" and append into it.

            ImGui::Text(
                    "This is some useful text.");  // Display some text (you can use a format strings too)
            ImGui::Checkbox(
                    "Demo Window",
                    &show_demo_window);  // Edit bools storing our window open/close state
            ImGui::Checkbox("Game Objects List", &showGameObjectsWindow);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color",
                              (float *) &clear_color);  // Edit 3 floats representing a color

            if (ImGui::Button("Button"))  // Buttons return true when clicked (most widgets return true
                // when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text(
                    "Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (showGameObjectsWindow) {
            ImGui::Begin("Game Objects");
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
                for (auto &kv: frameInfo.gameObjects) {
                    auto &gameObj = kv.second;
                    float scale = 1.f;
                    ImGui::PushID(static_cast<int>(gameObj.getId()));

                    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::AlignTextToFramePadding();
                    bool node_open = ImGui::TreeNode("Object", "%s-%u", gameObj.getName().c_str(),
                                                     static_cast<int>(gameObj.getId()));
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("Game Object");

                    if (node_open) {
                        ImGuiTreeNodeFlags flags =
                                ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
                                ImGuiTreeNodeFlags_Bullet;

                        ImGui::PushID("Scale Component");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Scale Component");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.scale.x, .01f);
                        gameObj.transform.scale.y = gameObj.transform.scale.x;
                        gameObj.transform.scale.z = gameObj.transform.scale.x;
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component X");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Translation X");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.translation.x, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component Y");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Translation Y");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.translation.y, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component Z");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Translation Z");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.translation.z, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component Rotation X");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Rotation X");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.rotation.x, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component Rotation Y");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Rotation Y");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.rotation.y, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Transform Component Rotation Z");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("TransformComponentField", flags, "Rotation Z");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::DragFloat("##value", &gameObj.transform.rotation.z, .01f);
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::PushID("Color Component");
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        ImGui::TreeNodeEx("Color", flags, "Color");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::SetNextItemWidth(-FLT_MIN);
                        ImGui::ColorEdit3("clear color",
                                          (float *) &clear_color);  // Edit 3 floats representing a color
                        gameObj.color.x = clear_color.x;
                        gameObj.color.y = clear_color.y;
                        gameObj.color.z = clear_color.z;
                        ImGui::NextColumn();
                        ImGui::PopID();

                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
            ImGui::End();
        }
    }
}