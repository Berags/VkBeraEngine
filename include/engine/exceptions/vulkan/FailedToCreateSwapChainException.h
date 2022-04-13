//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateSwapChainException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESWAPCHAINEXCEPTION_H
