//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef VKBERAENGINE_VALIDATIONLAYERNOTAVAILABLE_H
#define VKBERAENGINE_VALIDATIONLAYERNOTAVAILABLE_H

#include "../Exception.h"

namespace Engine::Exceptions {
    class ValidationLayersNotAvailable : public std::exception {
    public:
        explicit ValidationLayersNotAvailable() = default;

        [[nodiscard]] const char *what() const noexcept override {
            return "Validation Layers requested, but not available!";
        }
    };
}


#endif //VKBERAENGINE_VALIDATIONLAYERNOTAVAILABLE_H
