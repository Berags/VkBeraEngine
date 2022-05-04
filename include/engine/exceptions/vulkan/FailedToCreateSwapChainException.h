//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class FailedToCreateSwapChainException : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };
    }



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H
