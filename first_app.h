//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_FIRST_APP_H
#define MINIMINIMOTORWAYS_FIRST_APP_H

#include <memory>
#include <vector>
#include "include/engine/Core.h"

class FirstApp {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();

    ~FirstApp();

    FirstApp(const FirstApp &) = delete;

    FirstApp &operator=(const FirstApp &) = delete;

    void run();

private:
    void loadGameObjects();

    Engine::Window window{(std::string &) "VkBeraEngine", WIDTH, HEIGHT};
    Engine::Device device{window};
    Engine::Renderer renderer{window, device};

    std::unique_ptr<Engine::DescriptorPool> globalPool{};
    Engine::GameObject::Map gameObjects;
};


#endif //MINIMINIMOTORWAYS_FIRST_APP_H
