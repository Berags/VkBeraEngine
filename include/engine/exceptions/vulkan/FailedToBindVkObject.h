//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef VKBERAENGINE_FAILEDTOBINDVKOBJECT_H
#define VKBERAENGINE_FAILEDTOBINDVKOBJECT_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToBindVkObject : public std::exception {
    public:
        explicit FailedToBindVkObject(const char *vkObjectName)
                : message(std::string("Failed to find Vulkan Object: ") + std::string(vkObjectName)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        const std::string message;
    };
}


#endif //VKBERAENGINE_FAILEDTOBINDVKOBJECT_H
