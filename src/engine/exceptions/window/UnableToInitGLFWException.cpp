//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../../../include/engine/exceptions/window/UnableToInitGLFWException.h"

namespace Engine {
    namespace Exceptions {
        const char *UnableToInitGLFWException::what() const noexcept {
            return "Unable to init GLFW OpenGL library!";
        }
    }
}

