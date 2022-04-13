//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H
#define MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToFindVulkanSupportedGPUException : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPUEXCEPTION_H
