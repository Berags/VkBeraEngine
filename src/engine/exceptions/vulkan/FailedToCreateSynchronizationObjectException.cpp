//
// Created by Jacopo Beragnoli on 13/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateSynchronizationObjectException.h"

const char *Engine::Exceptions::FailedToCreateSynchronizationObjectException::what() const noexcept {
    return "Failed to create Synchronization Object for current frame! - Vulkan";
}
