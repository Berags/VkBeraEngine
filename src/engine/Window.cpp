//
// Created by Jacopo Beragnoli on 02/04/22.
//

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include "../../include/engine/Window.h"
#include "../../include/engine/exception/window/UnableToStartWindowException.h"
#include "../../include/engine/exception/window/UnableToInitGLFWException.h"

namespace Engine {
    Window::Window(std::string &name) : name(name), width(800), height(640) {
        std::cout << "Starting the glfwWindow\n";
        initWindow();
    }

    Window::~Window() {
        std::cout << "Closing the glfwWindow...\n";
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    void Window::initWindow() {
        if (!glfwInit())
            throw Engine::Exceptions::UnableToInitGLFWException();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        this->glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        /* Create a windowed mode glfwWindow and its OpenGL context */
        if (!glfwWindow) {
            glfwTerminate();
            throw Engine::Exceptions::UnableToStartWindowException();
        }
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";
    }

    GLFWwindow *Window::getGlfwWindow() const {
        return glfwWindow;
    }
}