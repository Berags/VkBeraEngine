#include <iostream>
#include <GLFW/glfw3.h>
#include "include/engine/exception/window/UnableToStartWindowException.h"
#include "include/engine/Window.h"
#include "include/engine/MainLoop.h"

int main() {
    auto *gameWindow(new Engine::Window());
    Engine::MainLoop mainLoop(gameWindow);
    mainLoop.updateGame();
    return 0;
}
