cmake_minimum_required(VERSION 3.21)
project(MiniminiMotorways)

set(CMAKE_CXX_STANDARD 17)
execute_process(
        COMMAND bash -c "${PROJECT_SOURCE_DIR}/shaders/compile.sh"
)

add_executable(MiniminiMotorways main.cpp src/engine/Window.cpp include/engine/Window.h src/engine/exceptions/Exception.cpp include/engine/exceptions/Exception.h src/engine/exceptions/window/UnableToStartWindowException.cpp include/engine/exceptions/window/UnableToStartWindowException.h src/engine/exceptions/window/UnableToInitGLFWException.cpp include/engine/exceptions/window/UnableToInitGLFWException.h src/engine/Pipeline.cpp include/engine/Pipeline.h src/engine/exceptions/file/UnableToOpenFileException.cpp include/engine/exceptions/file/UnableToOpenFileException.h src/engine/Device.cpp include/engine/Device.h src/engine/exceptions/window/FailedToCreateWindowSurfaceException.cpp include/engine/exceptions/window/FailedToCreateWindowSurfaceException.h src/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPUException.cpp include/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPUException.h src/engine/exceptions/vulkan/FailedToCreateShaderModuleException.cpp include/engine/exceptions/vulkan/FailedToCreateShaderModuleException.h src/engine/SwapChain.cpp include/engine/SwapChain.h first_app.cpp first_app.h src/engine/Model.cpp include/engine/Model.h src/engine/GameObject.cpp include/engine/GameObject.h src/engine/exceptions/vulkan/FailedToSubmitDrawCommandBufferException.cpp include/engine/exceptions/vulkan/FailedToSubmitDrawCommandBufferException.h src/engine/exceptions/vulkan/FailedToCreateSwapChainException.cpp include/engine/exceptions/vulkan/FailedToCreateSwapChainException.h src/engine/exceptions/vulkan/FailedToCreateTextureImageViewException.cpp include/engine/exceptions/vulkan/FailedToCreateTextureImageViewException.h src/engine/exceptions/vulkan/FailedToCreateSynchronizationObjectException.cpp include/engine/exceptions/vulkan/FailedToCreateSynchronizationObjectException.h src/engine/exceptions/vulkan/FailedToCreateRenderPassException.cpp include/engine/exceptions/vulkan/FailedToCreateRenderPassException.h src/engine/Renderer.cpp include/engine/Renderer.h src/engine/RenderSystem.cpp include/engine/RenderSystem.h src/engine/Camera.cpp include/engine/Camera.h src/engine/KeyboardMovementController.cpp include/engine/KeyboardMovementController.h src/engine/exceptions/vulkan/FailedToCreatePipeLineLayoutException.cpp include/engine/exceptions/vulkan/FailedToCreatePipeLineLayoutException.h include/libs/tiny_obj_loader.h include/engine/Utils.h src/engine/Buffer.cpp include/engine/Buffer.h include/engine/FrameInfo.h include/libs/stb_image.h src/engine/Descriptors.cpp include/engine/Descriptors.h include/libs/imgui/imconfig.h include/libs/imgui/imgui.cpp include/libs/imgui/imgui.h include/libs/imgui/imgui_demo.cpp include/libs/imgui/imgui_impl_glfw.cpp include/libs/imgui/imgui_impl_glfw.h include/libs/imgui/imgui_impl_vulkan.cpp include/libs/imgui/imgui_impl_vulkan.h include/libs/imgui/imgui_internal.h include/libs/imgui/imgui_tables.cpp include/libs/imgui/imgui_widgets.cpp include/libs/imgui/imstb_rectpack.h include/libs/imgui/imstb_textedit.h include/libs/imgui/imstb_truetype.h include/engine/ImGuiManager.cpp include/engine/ImGuiManager.h include/libs/imgui/imgui_draw.cpp)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
