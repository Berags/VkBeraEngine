//
// Created by Jacopo Beragnoli on 13/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToCreateSynchronizationObjectException :public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };

    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATESYNCHRONIZATIONOBJECTEXCEPTION_H
