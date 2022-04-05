//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../../../include/engine/exceptions/window/UnableToStartWindowException.h"

namespace Engine {
    namespace Exceptions {
        const char *UnableToStartWindowException::what() const noexcept {
            return "Unable to start the GLFW Window!";
        }
    }
}