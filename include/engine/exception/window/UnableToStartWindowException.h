//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class UnableToStartWindowException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}

#endif //MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
