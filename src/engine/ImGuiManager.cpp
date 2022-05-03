//
// Created by Jacopo Beragnoli on 26/04/22.
//

#include "../../include/engine/ImGuiManager.h"
#include <vulkan/vulkan_core.h>
#include <stdexcept>

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
        ImDrawData *pDrawData = ImGui::GetDrawData();
        ImGui_ImplVulkan_RenderDrawData(pDrawData, commandBuffer);
    }

    void ImGuiManager::run(Engine::FrameInfo &frameInfo) {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can
        // browse its code to learn more about Dear ImGui!).
        if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);
        bool showOverlay = true;
        ImGuiManager::ShowExampleAppSimpleOverlay(&showOverlay);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named
        // window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("VkBeraEngine - Debug");  // Create a window called "Hello, world!" and append into it.
            ImGui::Checkbox(
                    "Show Demo Window",
                    &showDemoWindow);  // Edit bools storing our window open/close state
            ImGui::Checkbox("Show Game Objects List", &showGameObjectsWindow);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (showGameObjectsWindow) {
            ImGui::Begin("Game Objects");
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            if (ImGui::Button("Save")) {
                json j;
                for (auto &kv: frameInfo.gameObjects) {
                    auto &obj = kv.second;
                    saveObjectToJson(obj, j);
                }
                std::ofstream o("../json/game_state.json");
                o << j;
                o.close();
                std::cout << "Game State saved to game_state.json\n";
            }
            ImGui::SameLine();
            if (ImGui::Button("Add Light")) {
                auto pointLight = Engine::GameObject::createPointLight(1.f);

                frameInfo.gameObjects.emplace(pointLight.getId(), std::move(pointLight));
                std::cout << "Added light\n";
            }
            ImGui::SameLine();
            if (ImGui::Button("Add Entity")) {
                showAddEntityWindow = true;
            }
            if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
                for (auto iterator = frameInfo.gameObjects.begin();
                     iterator != frameInfo.gameObjects.end(); ++iterator) {
                    auto &gameObj = iterator->second;
                    if (gameObj.pointLightComponent == nullptr) {
                        ImGui::PushID(static_cast<int>(gameObj.getId()));

                        // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        bool node_open = ImGui::TreeNode("Object", "%s", gameObj.name.c_str());
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("Game Object");

                        if (node_open) {
                            ImGuiTreeNodeFlags flags =
                                    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
                                    ImGuiTreeNodeFlags_Bullet;

                            ImGui::PushID("Name");
                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TreeNodeEx("TransformComponentField", flags, "Name");
                            ImGui::TableSetColumnIndex(1);
                            static char objName[128] = "";
                            strcpy(objName, gameObj.name.c_str());
                            ImGui::InputText("", objName, IM_ARRAYSIZE(objName));
                            gameObj.name = objName;
                            ImGui::NextColumn();
                            ImGui::PopID();

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

                            if (ImGui::Button("Delete"))
                                ImGui::OpenPopup("Delete?");
                            if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                                ImGui::Text(
                                        "This entity will be removed.\nThis operation cannot be undone!\n\n");
                                ImGui::Separator();

                                if (ImGui::Button("OK", ImVec2(120, 0))) {
                                    auto objectToDelete = iterator;
                                    iterator++;
                                    delete gameObj.model.get();
                                    ImGui::CloseCurrentPopup();
                                    frameInfo.gameObjects.erase(objectToDelete);
                                }
                                ImGui::SetItemDefaultFocus();
                                ImGui::SameLine();
                                if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                                ImGui::EndPopup();
                            }
                            ImGui::TreePop();
                        }
                        ImGui::PopID();
                    } else {
                        ImGui::PushID(static_cast<int>(gameObj.getId()));

                        // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::AlignTextToFramePadding();
                        bool node_open = ImGui::TreeNode("Object", "%s", gameObj.name.c_str());
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("Point Light");

                        if (node_open) {
                            ImGuiTreeNodeFlags flags =
                                    ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
                                    ImGuiTreeNodeFlags_Bullet;

                            ImGui::PushID("Name");
                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TreeNodeEx("TransformComponentField", flags, "Name");
                            ImGui::TableSetColumnIndex(1);
                            static char objName[128] = "";
                            strcpy(objName, gameObj.name.c_str());
                            ImGui::InputText("", objName, IM_ARRAYSIZE(objName));
                            gameObj.name = objName;
                            ImGui::NextColumn();
                            ImGui::PopID();

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

                            ImGui::PushID("Light Intensity");
                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TreeNodeEx("TransformComponentField", flags, "Light Intensity");
                            ImGui::TableSetColumnIndex(1);
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::DragFloat("##value", &gameObj.pointLightComponent->lightIntensity, .01f);
                            ImGui::NextColumn();
                            ImGui::PopID();

                            ImGui::PushID("Color Component");
                            ImVec4 colorVec4 = ImVec4(gameObj.color.x, gameObj.color.y, gameObj.color.z, 1.f);
                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            ImGui::AlignTextToFramePadding();
                            ImGui::TreeNodeEx("Color", flags, "Color");
                            ImGui::TableSetColumnIndex(1);
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::ColorEdit3("clear color",
                                              (float *) &colorVec4);  // Edit 3 floats representing a color
                            gameObj.color.x = colorVec4.x;
                            gameObj.color.y = colorVec4.y;
                            gameObj.color.z = colorVec4.z;
                            ImGui::NextColumn();
                            ImGui::PopID();

                            if (ImGui::Button("Delete"))
                                ImGui::OpenPopup("Delete?");
                            if (ImGui::BeginPopupModal("Delete?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                                ImGui::Text(
                                        "This entity will be removed.\nThis operation cannot be undone!\n\n");
                                ImGui::Separator();

                                if (ImGui::Button("OK", ImVec2(120, 0))) {
                                    auto objectToDelete = iterator;
                                    iterator++;
                                    frameInfo.gameObjects.erase(objectToDelete);
                                    ImGui::CloseCurrentPopup();
                                }
                                ImGui::SetItemDefaultFocus();
                                ImGui::SameLine();
                                if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
                                ImGui::EndPopup();
                            }

                            ImGui::TreePop();
                        }
                        ImGui::PopID();
                    }
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
            ImGui::End();
        }

        if (showAddEntityWindow) {
            ImGui::Begin("New Entity");

            static char objFileName[128] = "";
            ImGui::InputText("OBJ File Name: ", objFileName, IM_ARRAYSIZE(objFileName));

            if (ImGui::Button("Add")) {
                std::string objFullPath{"../models/"};
                objFullPath += objFileName;

                std::shared_ptr<Engine::Model> model = Engine::Model::createModelFromFile(device, objFullPath.c_str());
                auto gameObject = Engine::GameObject::createGameObject(objFileName);
                gameObject.model = model;

                frameInfo.gameObjects.emplace(gameObject.getId(), std::move(gameObject));

                std::cout << "Added entity with model file path: " << objFullPath << std::endl;
                showAddEntityWindow = false;
            }

            ImGui::End();
        }
    }

    void ImGuiManager::ShowExampleAppSimpleOverlay(bool *p_open) {
        const float PAD = 10.0f;
        static int corner = 0;
        ImGuiIO &io = ImGui::GetIO();
        ImGuiWindowFlags window_flags =
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (corner != -1) {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("Game Info", p_open, window_flags)) {
            //ImGui::Separator();
            ImGui::Text("FPS: %.1f - Frame Time %.3f", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
            /*if (ImGui::BeginPopupContextWindow()) {
                if (ImGui::MenuItem("Custom", nullptr, corner == -1)) corner = -1;
                if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) corner = 0;
                if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) corner = 1;
                if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) corner = 2;
                if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) corner = 3;
                if (p_open && ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndPopup();
            }*/
        }
        ImGui::End();
    }

    void ImGuiManager::saveObjectToJson(GameObject &obj, json &j) {
        json objJson;
        json vec3;
        json transformJson;

        vec3["x"] = obj.transform.translation.x;
        vec3["y"] = obj.transform.translation.y;
        vec3["z"] = obj.transform.translation.z;
        transformJson["translation"] = vec3;

        vec3["x"] = obj.transform.rotation.x;
        vec3["y"] = obj.transform.rotation.y;
        vec3["z"] = obj.transform.rotation.z;
        transformJson["rotation"] = vec3;

        vec3["x"] = obj.transform.scale.x;
        vec3["y"] = obj.transform.scale.y;
        vec3["z"] = obj.transform.scale.z;
        transformJson["scale"] = vec3;

        vec3["x"] = obj.color.x;
        vec3["y"] = obj.color.y;
        vec3["z"] = obj.color.z;
        transformJson["color"] = vec3;

        json model;
        if (obj.pointLightComponent == nullptr) {
            model["file_name"] = obj.model->getFilePath();
        } else {
            model["file_name"] = nullptr;
        }

        objJson["name"] = obj.name;
        objJson["transform"] = transformJson;
        objJson["model"] = model;
        j.push_back(objJson);
    }
}
