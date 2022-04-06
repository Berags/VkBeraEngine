//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULE_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULE_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateShaderModule : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULE_H
