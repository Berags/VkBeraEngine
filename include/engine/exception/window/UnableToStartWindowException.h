//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    class UnableToStartWindowException : public Engine::Exception {
    public:
        const char *what() const _NOEXCEPT override;
    };
}

#endif //MINIMINIMOTORWAYS_UNABLETOSTARTWINDOWEXCEPTION_H
