//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_WINDOW_H
#define MINIMINIMOTORWAYS_WINDOW_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <string>

namespace Engine {
    class Window {
    public:
        explicit Window(std::string &name, int width, int height);

        ~Window();

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        bool shouldClose() const;

        void swapBuffers() const;

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        VkExtent2D getExtent() {
            return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
        }

        int getHeight() const;

        int getWidth() const;

    private:
        GLFWwindow *glfwWindow;

        std::string name;
        int height;
        int width;

        void initWindow();
    };
}

#endif //MINIMINIMOTORWAYS_WINDOW_H
