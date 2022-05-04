//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class FailedToCreateRenderPassException : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };
    }



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATERENDERPASSEXCEPTION_H
