//
// Created by Jacopo Beragnoli on 06/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateShaderModule.h"

const char *Engine::Exceptions::FailedToCreateShaderModule::what() const noexcept {
    return "Failed to create shader module! - Vulkan";
}
