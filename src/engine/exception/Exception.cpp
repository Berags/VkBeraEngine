//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../../include/engine/exception/Exception.h"

namespace Engine {
    namespace Exceptions {
        const char *Exception::what() const noexcept {
            return exception::what();
        }
    }
}

