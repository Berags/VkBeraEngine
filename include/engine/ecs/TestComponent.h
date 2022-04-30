//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_TESTCOMPONENT_H
#define MINIMINIMOTORWAYS_TESTCOMPONENT_H

#include "IComponent.h"
#include <iostream>

namespace Engine::ECS {
    class TestComponent : public Engine::ECS::IComponent {
        void onUpdate(float dt) override {
            std::cout << "Updating the component - dt = " << dt << std::endl;
        }
    };
}


#endif //MINIMINIMOTORWAYS_TESTCOMPONENT_H
