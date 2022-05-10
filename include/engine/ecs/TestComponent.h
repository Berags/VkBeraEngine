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
        void onCreate() const override {
            std::cout << "On Create method" << std::endl;
        }

        void onUpdate(FrameInfo &frameInfo) override {
            std::cout << "On Update method" << std::endl;
        }

        void onDestroy() override {
            std::cout << "On destroy method" << std::endl;
        }
    };
}


#endif //MINIMINIMOTORWAYS_TESTCOMPONENT_H
