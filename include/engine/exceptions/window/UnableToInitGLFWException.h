//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef VKBERAENGINE_UNABLETOINITGLFWEXCEPTION_H
#define VKBERAENGINE_UNABLETOINITGLFWEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class UnableToInitGLFWException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Unable to init GLFW OpenGL library!";
        }
    };
}


#endif //VKBERAENGINE_UNABLETOINITGLFWEXCEPTION_H
