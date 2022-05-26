//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_APPLICATION_H
#define MINIMINIMOTORWAYS_APPLICATION_H

#include <memory>
#include <vector>
#include "include/engine/Window.h"
#include "include/engine/Renderer.h"
#include "include/engine/TextureStorage.h"
#include "include/engine/Descriptors.h"
#include "include/engine/GameObject.h"

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
    Engine::Window window{"VkBeraEngine", WIDTH, HEIGHT};
    Engine::Device device{window};
    Engine::Renderer renderer{window, device};
    Engine::TextureStorage textureStorage{device};

    std::unique_ptr<Engine::DescriptorPool> globalPool{};
    Engine::GameObject::Map gameObjects;
};


#endif //MINIMINIMOTORWAYS_APPLICATION_H
