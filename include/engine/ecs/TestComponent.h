//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_TESTCOMPONENT_H
#define MINIMINIMOTORWAYS_TESTCOMPONENT_H

#include "IComponent.h"
#include "../Window.h"
#include <iostream>

namespace Engine::ECS {
    class TestComponent : public Engine::ECS::IComponent {
    public:
        void onCreate() override {
            std::cout << "On Create function" << std::endl;
        }

        void onUpdate(float dt) override {
            IComponent::onUpdate(dt);
        }
    };
}


#endif //MINIMINIMOTORWAYS_TESTCOMPONENT_H
