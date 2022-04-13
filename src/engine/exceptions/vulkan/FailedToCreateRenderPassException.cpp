//
// Created by Jacopo Beragnoli on 13/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateRenderPassException.h"

const char *Engine::Exceptions::FailedToCreateRenderPassException::what() const noexcept {
    return "Failed to create Render Pass! - Vulkan";
}
