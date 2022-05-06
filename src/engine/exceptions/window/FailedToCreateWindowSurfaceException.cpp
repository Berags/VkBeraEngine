//
// Created by Jacopo Beragnoli on 06/04/22.
//

#include "../../../../include/engine/exceptions/window/FailedToCreateWindowSurfaceException.h"

const char *Engine::Exceptions::FailedToCreateWindowSurfaceException::what() const noexcept {
    return "Failed to create window getSurface! - Vulkan";
}
