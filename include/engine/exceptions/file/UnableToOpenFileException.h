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
        explicit UnableToOpenFileException(const char *fileName);

        [[nodiscard]] const char *what() const noexcept override;

    private:
        const std::string message;
    };
}


#endif //MINIMINIMOTORWAYS_UNABLETOOPENFILEEXCEPTION_H
