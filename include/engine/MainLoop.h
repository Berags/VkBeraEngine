//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_MAINLOOP_H
#define MINIMINIMOTORWAYS_MAINLOOP_H

#include "Window.h"

namespace Engine {
    class MainLoop {
    public:
        explicit MainLoop(Window *window);
        void updateGame();
    private:
        Engine::Window *window;
    };
}


#endif //MINIMINIMOTORWAYS_MAINLOOP_H
