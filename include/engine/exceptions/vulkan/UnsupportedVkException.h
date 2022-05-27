//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef MINIMINIMOTORWAYS_UNSUPPORTEDVKEXCEPTION_H
#define MINIMINIMOTORWAYS_UNSUPPORTEDVKEXCEPTION_H

#include <utility>

#include "../Exception.h"

namespace Engine::Exceptions {
    class UnsupportedVkException : public std::exception {
    public:
        explicit UnsupportedVkException(const char *vkInvalidArgument) : message("Unsupported VK Argument: ",
                                                                                 vkInvalidArgument) {}

        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}


#endif //MINIMINIMOTORWAYS_UNSUPPORTEDVKEXCEPTION_H
