//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../include/engine/MainLoop.h"
#include <string>

namespace Engine {
    MainLoop::MainLoop(Engine::Window *window) : window(window) {}

    void MainLoop::start() {

        // call to the update method that will draw graphics to the screen
        update();

        // when update is done we call the stop function that deletes the window
        stop();
    }

    void MainLoop::stop() {
        delete window;
    }

    void MainLoop::update() const {
        while (!window->shouldClose()) {
            // Calling the main render function
            render();

            // Swap front and back buffers
            window->swapBuffers();

            // Poll for and process events
            glfwPollEvents();
        }
    }

    void MainLoop::render() {

    }
}