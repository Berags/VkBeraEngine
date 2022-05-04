//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H

#include "../Exception.h"

namespace Engine::Exceptions {
        class FailedToCreateSynchronizationObjectException :public std::exception {
        public:
            [[nodiscard]] const char *what() const noexcept override;
        };

    }


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H
