//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_MAINLOOP_H
#define MINIMINIMOTORWAYS_MAINLOOP_H

#include "Window.h"
#include "Pipeline.h"
#include "SwapChain.h"
#include <vector>
#include <memory>

namespace Engine {
    class MainLoop {
    public:
        explicit MainLoop(Window *window);

        virtual ~MainLoop();

        MainLoop(const MainLoop &) = delete;

        MainLoop &operator=(const MainLoop &) = delete;

        void start();

    private:
        Engine::Window *window;
        Engine::Device device{*window};
        SwapChain swapChain{device, window->getExtent()};
        std::unique_ptr<Pipeline> pipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;

        void createPipelineLayout();

        void createPipeline();

        void createCommandBuffers();
        void drawFrame();

        static void render();

        void update() const;

        void stop();
    };
}


#endif //MINIMINIMOTORWAYS_MAINLOOP_H
