//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateRenderPassException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H
