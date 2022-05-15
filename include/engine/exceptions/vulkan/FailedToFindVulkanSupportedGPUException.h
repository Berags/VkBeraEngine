//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToFindVulkanSupportedGPUException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "No GPU with Vulkan support was found!";
        }
    };
}


#endif //MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H
