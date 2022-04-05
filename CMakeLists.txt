cmake_minimum_required(VERSION 3.21)
project(MiniminiMotorways)

set(CMAKE_CXX_STANDARD 14)

add_executable(MiniminiMotorways main.cpp src/engine/Window.cpp include/engine/Window.h src/engine/exception/Exception.cpp include/engine/exception/Exception.h src/engine/exception/window/UnableToStartWindowException.cpp include/engine/exception/window/UnableToStartWindowException.h src/engine/exception/window/UnableToInitGLFWException.cpp include/engine/exception/window/UnableToInitGLFWException.h src/engine/MainLoop.cpp include/engine/MainLoop.h)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
