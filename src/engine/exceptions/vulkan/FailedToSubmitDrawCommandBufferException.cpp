//
// Created by Jacopo Beragnoli on 13/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToSubmitDrawCommandBufferException.h"

const char *Engine::Exceptions::FailedToSubmitDrawCommandBufferException::what() const noexcept {
    return "Failed to submit draw command buffer! - Vulkan";
}
