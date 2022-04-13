//
// Created by Jacopo Beragnoli on 13/04/22.
//

#include "../../../../include/engine/exceptions/vulkan/FailedToCreateTextureImageViewException.h"

const char *Engine::Exceptions::FailedToCreateTextureImageViewException::what() const noexcept {
    return "Failed to create Texture Image View! - Vulkan";
}
