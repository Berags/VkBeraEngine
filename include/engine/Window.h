//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef VKBERAENGINE_WINDOW_H
#define VKBERAENGINE_WINDOW_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <string>

namespace Engine {
    class Window {
    public:
        Window(const char *name, int width, int height);

        ~Window();

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        [[nodiscard]] bool shouldClose() const;

        [[nodiscard]] bool wasWindowResized() const;

        void resetWindowResizedFlag();

        void swapBuffers() {
            glfwSwapBuffers(this->glfwWindow);
        }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        void setCursorPositionToCenter();

        [[nodiscard]] VkExtent2D getExtent() const {
            return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
        }

        [[nodiscard]] int getHeight() const {
            return height;
        }

        [[nodiscard]] int getWidth() const {
            return width;
        }

        [[nodiscard]] GLFWwindow *getGlfwWindow() const;

        [[nodiscard]] float getMouseX() const;

        [[nodiscard]] float getMouseY() const;

    private:
        GLFWwindow *glfwWindow;

        std::string name;
        int height;
        int width;

        float mouseX;
        float mouseY;

        // True if the window was resized during last frame buffer draw
        bool frameBufferResized = false;

        void initWindow();

        static void frameBufferResizedCallback(GLFWwindow *glfWwindow, int width, int height);

        static void cursorPositionCallback(GLFWwindow *glfWwindow, double xPos, double yPos);
    };
}

#endif //VKBERAENGINE_WINDOW_H
