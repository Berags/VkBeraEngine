//
// Created by Jacopo Beragnoli on 05/04/22.
//

#ifndef MINIMINIMOTORWAYS_UNABLETOOPENFILEEXCEPTION_H
#define MINIMINIMOTORWAYS_UNABLETOOPENFILEEXCEPTION_H

#include <string>
#include "../Exception.h"

namespace Engine::Exceptions {
    class UnableToOpenFileException : public std::exception {
    public:
        explicit UnableToOpenFileException(std::string fileName);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        const std::string fileName;
    };
}


#endif //MINIMINIMOTORWAYS_UNABLETOOPENFILEEXCEPTION_H
