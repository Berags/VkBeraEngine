//
// Created by Jacopo Beragnoli on 12/04/22.
//

#ifndef MINIMINIMOTORWAYS_FIRST_APP_H
#define MINIMINIMOTORWAYS_FIRST_APP_H

#include <memory>
#include <vector>
#include "include/engine/Window.h"
#include "include/engine/Device.h"
#include "include/engine/SwapChain.h"
#include "include/engine/Pipeline.h"
#include "include/engine/Model.h"

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
    void loadModels();
    void createPipelineLayout();

    void createPipeline();

    void createCommandBuffers();

    void drawFrame();

    Engine::Window lveWindow{(std::string &) "Ciao", WIDTH, HEIGHT};
    Engine::Device lveDevice{lveWindow};
    Engine::SwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};
    std::unique_ptr<Engine::Pipeline> lvePipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<Engine::Model> model;
};


#endif //MINIMINIMOTORWAYS_FIRST_APP_H
