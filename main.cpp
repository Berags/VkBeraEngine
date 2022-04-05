#include <iostream>
#include <string>
#include "include/engine/Window.h"
#include "include/engine/MainLoop.h"

int main() {
    std::string windowName = "MiniMini Motorways";
    auto *gameWindow(new Engine::Window(windowName, 800, 600));
    Engine::MainLoop mainLoop(gameWindow);
    mainLoop.start();
    return 0;
}
