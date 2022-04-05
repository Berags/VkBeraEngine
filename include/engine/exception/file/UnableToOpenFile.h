//
// Created by Jacopo Beragnoli on 05/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOOPENFILE_H
#define MINIMINIMOTORWAYS_UNABLETOOPENFILE_H

#include <string>
#include "../Exception.h"

namespace Engine {
    namespace Exceptions {
        class UnableToOpenFile : public Engine::Exceptions::Exception {
        public:
            UnableToOpenFile(std::string fileName);

            const char *what() const noexcept override;

        private:
            const std::string fileName;
        };
    }
}


#endif //MINIMINIMOTORWAYS_UNABLETOOPENFILE_H
