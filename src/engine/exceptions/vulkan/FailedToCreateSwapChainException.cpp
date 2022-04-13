//
// Created by Jacopo Beragnoli on 13/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateSwapChainException.h"

const char *Engine::Exceptions::FailedToCreateSwapChainException::what() const noexcept {
    return "Failed to create Swap Chain! - Vulkan";
}
