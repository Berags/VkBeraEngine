//
// Created by Jacopo Beragnoli on 06/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToFindVulkanSupportedGPU.h"

const char *Engine::Exceptions::FailedToFindVulkanSupportedGPU::what() const noexcept {
    return "No GPU with Vulkan support was found!";
}
