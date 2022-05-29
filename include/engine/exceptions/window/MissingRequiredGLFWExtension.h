//
// Created by Jacopo Beragnoli on 26/05/22.
//

#ifndef VKBERAENGINE_MISSINGREQUIREDGLFWEXTENSION_H
#define VKBERAENGINE_MISSINGREQUIREDGLFWEXTENSION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class MissingRequiredGLFWExtension : public std::exception {
    public:
        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return "Missing Required GLFW Extension!";
        }
    };
} // Exceptions

#endif //VKBERAENGINE_MISSINGREQUIREDGLFWEXTENSION_H
