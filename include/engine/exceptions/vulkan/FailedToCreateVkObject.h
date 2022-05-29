//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef VKBERAENGINE_FAILEDTOCREATEVKOBJECT_H
#define VKBERAENGINE_FAILEDTOCREATEVKOBJECT_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToCreateVkObject : public std::exception {
    public:
        explicit FailedToCreateVkObject(const char *vkObjectName)
                : message(std::string("Failed to create Vulkan Object: ") + std::string(vkObjectName)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        const std::string message;
    };
}


#endif //VKBERAENGINE_FAILEDTOCREATEVKOBJECT_H
