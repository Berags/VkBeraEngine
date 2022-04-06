cmake_minimum_required(VERSION 3.21)
project(MiniminiMotorways)

set(CMAKE_CXX_STANDARD 14)

add_executable(MiniminiMotorways main.cpp src/engine/Window.cpp include/engine/Window.h src/engine/exceptions/Exception.cpp include/engine/exceptions/Exception.h src/engine/exceptions/window/UnableToStartWindowException.cpp include/engine/exceptions/window/UnableToStartWindowException.h src/engine/exceptions/window/UnableToInitGLFWException.cpp include/engine/exceptions/window/UnableToInitGLFWException.h src/engine/MainLoop.cpp include/engine/MainLoop.h src/engine/Pipeline.cpp include/engine/Pipeline.h src/engine/exceptions/file/UnableToOpenFile.cpp include/engine/exceptions/file/UnableToOpenFile.h src/engine/Device.cpp include/engine/Device.h src/engine/exceptions/window/FailedToCreateWindowSurfaceException.cpp include/engine/exceptions/window/FailedToCreateWindowSurfaceException.h src/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPU.cpp include/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPU.h src/engine/exceptions/vulkan/FailedToCreateShaderModule.cpp include/engine/exceptions/vulkan/FailedToCreateShaderModule.h)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
