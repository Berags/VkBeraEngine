//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateWindowSurfaceException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}



#endif //MINIMINIMOTORWAYS_FAILEDTOCREATEWINDOWSURFACEEXCEPTION_H
