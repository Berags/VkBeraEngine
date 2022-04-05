//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../include/engine/Pipeline.h"
#include "../../include/engine/exceptions/file/UnableToOpenFile.h"
#include <fstream>
#include <iostream>

namespace Engine {
    Pipeline::Pipeline(const std::string &vertFilePath, const std::string &fragFilePath) {
        createGraphicsPipeline(vertFilePath, fragFilePath);
    }

    std::vector<char> Pipeline::readFile(const std::string &filePath) {
        std::ifstream file{filePath, std::ios::ate | std::ios::binary};

        if (!file.is_open()) {
            throw Engine::Exceptions::UnableToOpenFile(filePath);
        }

        long fileSize = static_cast<long>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();

        return buffer;
    }

    void Pipeline::createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath) {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex shader file size: " << vertCode.size() << "\n";
        std::cout << "Fragment file size: " << fragCode.size() << "\n";
    }
}
