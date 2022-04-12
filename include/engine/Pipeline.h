//
// Created by Jacopo Beragnoli on 05/04/22.
//

#ifndef MINIMINIMOTORWAYS_PIPELINE_H
#define MINIMINIMOTORWAYS_PIPELINE_H

#include <string>
#include <vector>
#include "Device.h"

namespace Engine {
    struct PipelineConfigInfo {
        PipelineConfigInfo() = default;

        PipelineConfigInfo(const PipelineConfigInfo &) = delete;

        PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

        VkViewport viewport{};
        VkRect2D scissor{};
        VkPipelineViewportStateCreateInfo viewportInfo{};
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
        VkPipelineRasterizationStateCreateInfo rasterizationInfo{};
        VkPipelineMultisampleStateCreateInfo multisampleInfo{};
        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };


    class Pipeline {
    public:
        Pipeline(Engine::Device &device, const std::string &vertFilePath, const std::string &fragFilePath,
                 const PipelineConfigInfo &configInfo);

        virtual ~Pipeline();

        Pipeline(const Pipeline &) = delete;

        void operator=(const Pipeline &) = delete;

        static void defaultConfigInfo(PipelineConfigInfo &configInfo, uint32_t width, uint32_t height);

        void bind(VkCommandBuffer commandBuffer);

    private:
        static std::vector<char> readFile(const std::string &filePath);

        Engine::Device &device;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;

        void createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,
                                    const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);
    };
}


#endif //MINIMINIMOTORWAYS_PIPELINE_H
