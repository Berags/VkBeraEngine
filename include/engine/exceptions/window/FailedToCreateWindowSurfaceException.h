//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef VKBERAENGINE_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H
#define VKBERAENGINE_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToCreateWindowSurfaceException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Failed to create window getSurface! - Vulkan";
        }
    };
}


#endif //VKBERAENGINE_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H
