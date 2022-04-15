cmake_minimum_required(VERSION 3.21)
project(MiniminiMotorways)

set(CMAKE_CXX_STANDARD 14)
execute_process(
        COMMAND bash -c "${PROJECT_SOURCE_DIR}/shaders/compile.sh"
)

add_executable(MiniminiMotorways main.cpp src/engine/Window.cpp include/engine/Window.h src/engine/exceptions/Exception.cpp include/engine/exceptions/Exception.h src/engine/exceptions/window/UnableToStartWindowException.cpp include/engine/exceptions/window/UnableToStartWindowException.h src/engine/exceptions/window/UnableToInitGLFWException.cpp include/engine/exceptions/window/UnableToInitGLFWException.h src/engine/Pipeline.cpp include/engine/Pipeline.h src/engine/exceptions/file/UnableToOpenFileException.cpp include/engine/exceptions/file/UnableToOpenFileException.h src/engine/Device.cpp include/engine/Device.h src/engine/exceptions/window/FailedToCreateWindowSurfaceException.cpp include/engine/exceptions/window/FailedToCreateWindowSurfaceException.h src/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPUException.cpp include/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPUException.h src/engine/exceptions/vulkan/FailedToCreateShaderModuleException.cpp include/engine/exceptions/vulkan/FailedToCreateShaderModuleException.h src/engine/SwapChain.cpp include/engine/SwapChain.h first_app.cpp first_app.h src/engine/Model.cpp include/engine/Model.h src/engine/GameObject.cpp include/engine/GameObject.h src/engine/exceptions/vulkan/FailedToSubmitDrawCommandBufferException.cpp include/engine/exceptions/vulkan/FailedToSubmitDrawCommandBufferException.h src/engine/exceptions/vulkan/FailedToCreateSwapChainException.cpp include/engine/exceptions/vulkan/FailedToCreateSwapChainException.h src/engine/exceptions/vulkan/FailedToCreateTextureImageViewException.cpp include/engine/exceptions/vulkan/FailedToCreateTextureImageViewException.h src/engine/exceptions/vulkan/FailedToCreateSynchronizationObjectException.cpp include/engine/exceptions/vulkan/FailedToCreateSynchronizationObjectException.h src/engine/exceptions/vulkan/FailedToCreateRenderPassException.cpp include/engine/exceptions/vulkan/FailedToCreateRenderPassException.h src/engine/Renderer.cpp include/engine/Renderer.h src/engine/RenderSystem.cpp include/engine/RenderSystem.h src/engine/Camera.cpp include/engine/Camera.h src/engine/KeyboardMovementController.cpp include/engine/KeyboardMovementController.h)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
