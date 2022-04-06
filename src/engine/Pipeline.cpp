//
// Created by Jacopo Beragnoli on 05/04/22.
//

#include "../../include/engine/Pipeline.h"
#include "../../include/engine/Device.h"
#include "../../include/engine/exceptions/file/UnableToOpenFile.h"
#include "../../include/engine/exceptions/vulkan/FailedToCreateShaderModule.h"
#include <fstream>
#include <iostream>

namespace Engine {
    Pipeline::Pipeline(Engine::Device &device, const std::string &vertFilePath, const std::string &fragFilePath,
                       const PipelineConfigInfo &configInfo) : device{device} {
        createGraphicsPipeline(vertFilePath, fragFilePath, configInfo);

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

    Pipeline::~Pipeline() {

    }

    void Pipeline::createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,
                                          const PipelineConfigInfo &configInfo) {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex shader file size: " << vertCode.size() << "\n";
        std::cout << "Fragment file size: " << fragCode.size() << "\n";
    }

    void Pipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

        if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
            throw Engine::Exceptions::FailedToCreateShaderModule();
    }

    PipelineConfigInfo Pipeline::defaultConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }

}
