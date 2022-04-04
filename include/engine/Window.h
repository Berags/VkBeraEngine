//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_WINDOW_H
#define MINIMINIMOTORWAYS_WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

namespace Engine {
    class Window {
    public:
        explicit Window(std::string &name);

        ~Window();

        GLFWwindow *getGlfwWindow() const;

    private:
        GLFWwindow *glfwWindow{};

        std::string name;
        GLsizei height;
        GLsizei width;

        void initWindow();
    };
}

#endif //MINIMINIMOTORWAYS_WINDOW_H
