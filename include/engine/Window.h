//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_WINDOW_H
#define MINIMINIMOTORWAYS_WINDOW_H

#include <GLFW/glfw3.h>

namespace Engine {
    class Window {
    public:
        Window();

        ~Window();

        GLFWwindow *getWindow() const;

    private:
        GLFWwindow *window;

        void initWindow();
    };
}

#endif //MINIMINIMOTORWAYS_WINDOW_H
