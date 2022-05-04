//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class FailedToCreateShaderModuleException : public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };
    }


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESHADERMODULEEXCEPTION_H
