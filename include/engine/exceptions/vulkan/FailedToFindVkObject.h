//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef MINIMINIMOTORWAYS_FAILEDTOFINDVKOBJECT_H
#define MINIMINIMOTORWAYS_FAILEDTOFINDVKOBJECT_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class FailedToFindVkObject : public std::exception {
    public:
        explicit FailedToFindVkObject(const char *vkObjectName)
                : message(std::string("Failed to find Vulkan Object: ") + std::string(vkObjectName)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        const std::string message;
    };
}


#endif //MINIMINIMOTORWAYS_FAILEDTOFINDVKOBJECT_H
