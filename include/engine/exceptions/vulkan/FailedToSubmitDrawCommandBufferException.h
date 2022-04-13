//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToSubmitDrawCommandBufferException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}



#endif //MINIMINIMOTORWAYS_FAILEDTOSUBMITDRAWCOMMANDBUFFEREXCEPTION_H
