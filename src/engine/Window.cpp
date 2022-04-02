//
// Created by Jacopo Beragnoli on 02/04/22.
//


#include <exception>
#include <iostream>
#include "../../include/engine/Window.h"
#include "../../include/engine/exception/window/UnableToStartWindowException.h"
#include "../../include/engine/exception/window/UnableToInitGLFWException.h"

namespace Engine {
    Window::Window() {
        initWindow();
    }

    Window::~Window() {
        std::cout << "Closing the window...\n";
        glfwTerminate();
    }

    void Window::initWindow() {
        if(!glfwInit())
            throw Engine::UnableToInitGLFWException();

        this->window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
        /* Create a windowed mode window and its OpenGL context */
        if (!window)
        {
            glfwTerminate();
            throw Engine::UnableToStartWindowException();
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(window);
    }

    GLFWwindow *Window::getWindow() const {
        return window;
    }
}