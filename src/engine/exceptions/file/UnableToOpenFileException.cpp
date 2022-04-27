//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../../../include/engine/exceptions/file/UnableToOpenFileException.h"

#include <utility>

const char *Engine::Exceptions::UnableToOpenFileException::what() const noexcept {
    return "Unable to open selected file!";
}

Engine::Exceptions::UnableToOpenFileException::UnableToOpenFileException(std::string fileName) : fileName(std::move(
        fileName)) {}
