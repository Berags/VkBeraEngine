cmake_minimum_required(VERSION 3.21)
project(MiniminiMotorways)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(MiniminiMotorways main.cpp src/engine/Window.cpp include/engine/Window.h src/engine/exception/Exception.cpp include/engine/exception/Exception.h src/engine/exception/window/UnableToStartWindowException.cpp include/engine/exception/window/UnableToStartWindowException.h src/engine/exception/window/UnableToInitGLFWException.cpp include/engine/exception/window/UnableToInitGLFWException.h src/MainLoop.cpp include/engine/MainLoop.h)

target_link_libraries(MiniminiMotorways glfw)
target_link_libraries(MiniminiMotorways OpenGL::GL)
