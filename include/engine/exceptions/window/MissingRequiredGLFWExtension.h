//
// Created by Jacopo Beragnoli on 26/05/22.
//

#ifndef MINIMINIMOTORWAYS_MISSINGREQUIREDGLFWEXTENSION_H
#define MINIMINIMOTORWAYS_MISSINGREQUIREDGLFWEXTENSION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class MissingRequiredGLFWExtension : public std::exception {
    public:
        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return "Missing Required GLFW Extension!";
        }
    };
} // Exceptions

#endif //MINIMINIMOTORWAYS_MISSINGREQUIREDGLFWEXTENSION_H
