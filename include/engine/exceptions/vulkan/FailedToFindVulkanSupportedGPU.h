//
// Created by Jacopo Beragnoli on 06/04/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPU_H
#define MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPU_H

#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class FailedToFindVulkanSupportedGPU : public Engine::Exceptions::Exception {
        public:
            const char *what() const noexcept override;
        };
    }
}


#endif //MINIMINIMOTORWAYS_FAILEDTOFINDVULKANSUPPORTEDGPU_H
