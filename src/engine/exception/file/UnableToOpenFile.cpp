//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../../../include/engine/exception/file/UnableToOpenFile.h"

#include <utility>

const char *Engine::Exceptions::UnableToOpenFile::what() const noexcept {
    std::string error = "Unable to open selected file!\nSelected file is: " + fileName;
    return error.c_str();
}

Engine::Exceptions::UnableToOpenFile::UnableToOpenFile(std::string fileName) : fileName(std::move(fileName)) {}
