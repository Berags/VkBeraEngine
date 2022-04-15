//
// Created by Jacopo Beragnoli on 15/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreatePipeLineLayoutException.h"

const char *Engine::Exceptions::FailedToCreatePipeLineLayoutException::what() const noexcept {
    return "Failed to create Pipeline layout! - Vulkan";
}
