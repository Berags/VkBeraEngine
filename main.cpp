#include <string>
#include <iostream>
#include "include/engine/Window.h"
#include "include/engine/MainLoop.h"
#include "first_app.h"

int main() {
    /*std::string windowName = "MiniMini Motorways";
    auto *gameWindow = new Engine::Window(windowName, 800, 600);;
    Engine::MainLoop mainLoop(gameWindow);
    mainLoop.start();*/
    FirstApp app{};

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
