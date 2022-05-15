//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToSubmitDrawCommandBufferException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Failed to submit draw command buffer! - Vulkan";
        }
    };
}


#endif //MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H
