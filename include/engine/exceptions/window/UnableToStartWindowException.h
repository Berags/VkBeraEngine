//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class UnableToStartWindowException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Unable to start the GLFW Window!";
        }
    };
}

#endif //MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
