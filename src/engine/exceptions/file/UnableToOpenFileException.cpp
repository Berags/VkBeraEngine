//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../../../include/engine/exceptions/file/UnableToOpenFileException.h"

#include <utility>

const char *Engine::Exceptions::UnableToOpenFileException::what() const noexcept {
    return message.c_str();
}

Engine::Exceptions::UnableToOpenFileException::UnableToOpenFileException(const char *fileName) : message(
        std::string("Unable to open selected file! - File Name: ") + std::string(fileName)) {}
