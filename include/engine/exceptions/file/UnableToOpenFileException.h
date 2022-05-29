//
// Created by Jacopo Beragnoli on 05/04/22.
//

#ifndef VKBERAENGINE_UNABLETOOPENFILEEXCEPTION_H
#define VKBERAENGINE_UNABLETOOPENFILEEXCEPTION_H

#include <string>
#include "../Exception.h"

namespace Engine::Exceptions {
    class UnableToOpenFileException : public std::exception {
    public:
        explicit UnableToOpenFileException(const char *fileName) : message(
                std::string("Unable to open selected file! - File Name: ") + std::string(fileName)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        const std::string message;
    };
}


#endif //VKBERAENGINE_UNABLETOOPENFILEEXCEPTION_H
