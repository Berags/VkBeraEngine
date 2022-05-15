//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_APPLICATION_H
#define MINIMINIMOTORWAYS_APPLICATION_H

#include <memory>
#include <vector>
#include "include/engine/Core.h"

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Application();

    ~Application();

    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    void run();

private:
    Engine::Window window{(std::string &) "VkBeraEngine", WIDTH, HEIGHT};
    Engine::Device device{window};
    Engine::Renderer renderer{window, device};

    std::unique_ptr<Engine::DescriptorPool> globalPool{};
    Engine::GameObject::Map gameObjects;
};


#endif //MINIMINIMOTORWAYS_APPLICATION_H
