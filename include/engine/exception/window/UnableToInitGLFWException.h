//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    class UnableToInitGLFWException : public Engine::Exception {
    public:
        const char *what() const _NOEXCEPT override;
    };
}


#endif //MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
