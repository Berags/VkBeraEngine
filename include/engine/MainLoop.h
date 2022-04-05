//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_MAINLOOP_H
#define MINIMINIMOTORWAYS_MAINLOOP_H

#include "Window.h"
#include "Pipeline.h"

namespace Engine {
    class MainLoop {
    public:
        explicit MainLoop(Window *window);

        void start();

    private:
        Engine::Window *window;

        Pipeline pipeline{"../shaders/simple_shader.vert.spv", "../shaders/simple_shader.frag.spv"};

        static void render();

        void update() const;

        void stop();
    };
}


#endif //MINIMINIMOTORWAYS_MAINLOOP_H
