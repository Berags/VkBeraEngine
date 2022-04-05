//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_EXCEPTION_H
#define MINIMINIMOTORWAYS_EXCEPTION_H

#include <exception>

namespace Engine {
    namespace Exceptions {
        class Exception : public std::exception {
        public:
            const char *what() const noexcept override;
            //virtual void sendErrorMessage() const;
        };
    }
}

#endif //MINIMINIMOTORWAYS_EXCEPTION_H
