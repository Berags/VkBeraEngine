//
// Created by Jacopo Beragnoli on 06/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateShaderModuleException.h"

const char *Engine::Exceptions::FailedToCreateShaderModuleException::what() const noexcept {
    return "Failed to create shader module! - Vulkan";
}
