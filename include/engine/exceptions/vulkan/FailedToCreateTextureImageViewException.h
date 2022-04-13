//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateTextureImageViewException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATETEXTUREIMAGEVIEWEXCEPTION_H
