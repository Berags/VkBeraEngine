//
// Created by Jacopo Beragnoli on 29/05/22.
//

#ifndef VKBERAENGINE_FAILEDTOLOADFILEEXCEPTION_H
#define VKBERAENGINE_FAILEDTOLOADFILEEXCEPTION_H

#include <exception>

namespace Engine::Exceptions {
    class FailedToLoadFileException : public std::exception {
    public:
        explicit FailedToLoadFileException(const char *fileName) : message(
                std::string("Unable to load selected file! - File Path: ") + std::string(fileName)) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message.c_str();
        }

    private:
        const std::string message{};
    };
} // Engine::Exceptions

#endif //VKBERAENGINE_FAILEDTOLOADFILEEXCEPTION_H
