//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateShaderModuleException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H
