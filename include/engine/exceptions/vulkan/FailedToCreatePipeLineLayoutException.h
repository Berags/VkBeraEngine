//
// Created by Jacopo Beragnoli on 15/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOCREATEPIPELINELAYOUTEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOCREATEPIPELINELAYOUTEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {

        class FailedToCreatePipeLineLayoutException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOCREATEPIPELINELAYOUTEXCEPTION_H
