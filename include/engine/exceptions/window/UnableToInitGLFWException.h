//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class UnableToInitGLFWException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_UNABLETOINITGLFWEXCEPTION_H
