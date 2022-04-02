//
// Created by Jacopo Beragnoli on 02/04/22.
//


#include <exception>
#include "../../include/engine/Window.h"
#include "../../include/engine/exception/window/UnableToStartWindowException.h"

namespace Engine {
    Window::Window() {
        if(!glfwInit())
            throw "GLFW Library not found!";

        this->window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        /* Create a windowed mode window and its OpenGL context */
        if (!window)
        {
            glfwTerminate();
            throw Engine::UnableToStartWindowException();
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(window);
    }

    Window::~Window() {

    }
}