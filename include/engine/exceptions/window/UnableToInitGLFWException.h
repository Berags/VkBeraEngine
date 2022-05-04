//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class UnableToInitGLFWException : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };
    }


#endif //MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
