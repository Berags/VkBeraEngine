//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../../../include/engine/exceptions/file/UnableToOpenFileException.h"

#include <utility>

const char *Engine::Exceptions::UnableToOpenFileException::what() const noexcept {
    std::string error = "Unable to open selected file!\nSelected file is: " + fileName;
    return error.c_str();
}

Engine::Exceptions::UnableToOpenFileException::UnableToOpenFileException(const std::string &fileName) : fileName(
        std::move(fileName)) {}
