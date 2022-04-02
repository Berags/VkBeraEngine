//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../include/engine/MainLoop.h"

namespace Engine {
    MainLoop::MainLoop(Engine::Window *window) : window(window) {}

    void MainLoop::updateGame() {
        while (!glfwWindowShouldClose(window->getWindow())) {
            // Render here
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap front and back buffers
            glfwSwapBuffers(window->getWindow());

            // Poll for and process events
            glfwPollEvents();
        }
        delete window;
    }
}