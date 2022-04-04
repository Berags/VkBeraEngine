//
// Created by Jacopo Beragnoli on 02/04/22.
//


#include <exception>
#include <iostream>
#include <OpenGL/glu.h>
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
        glfwTerminate();
    }

    void Window::initWindow() {
        if (!glfwInit())
            throw Engine::Exceptions::UnableToInitGLFWException();

        this->glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        /* Create a windowed mode glfwWindow and its OpenGL context */
        if (!glfwWindow) {
            glfwTerminate();
            throw Engine::Exceptions::UnableToStartWindowException();
        }
        /* Make the glfwWindow's context current */
        glfwMakeContextCurrent(glfwWindow);

    }

    GLFWwindow *Window::getGlfwWindow() const {
        return glfwWindow;
    }
}