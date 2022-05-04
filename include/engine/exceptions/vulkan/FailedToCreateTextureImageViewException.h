//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class FailedToCreateTextureImageViewException : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };
    }



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H
