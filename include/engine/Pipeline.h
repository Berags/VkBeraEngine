//
// Created by Jacopo Beragnoli on 05/04/22.
//

#ifndef MINIMINIMOTORWAYS_PIPELINE_H
#define MINIMINIMOTORWAYS_PIPELINE_H

#include <string>
#include <vector>

namespace Engine {
    class Pipeline {
    public:
        Pipeline(const std::string &vertFilePath, const std::string &fragFilePath);

    private:
        static std::vector<char> readFile(const std::string &filePath);
        void createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath);
    };
}


#endif //MINIMINIMOTORWAYS_PIPELINE_H
