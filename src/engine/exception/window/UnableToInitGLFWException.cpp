//
// Created by Jacopo Beragnoli on 02/04/22.
//

#include "../../../../include/engine/exception/window/UnableToInitGLFWException.h"

const char *Engine::UnableToInitGLFWException::what() const noexcept {
    return "Unable to init GLFW OpenGL library!";
}
