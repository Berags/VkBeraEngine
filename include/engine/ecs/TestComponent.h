//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_TESTCOMPONENT_H
#define MINIMINIMOTORWAYS_TESTCOMPONENT_H

#include "IComponent.h"
#include "../Window.h"
#include <iostream>

namespace Engine::ECS {
    class TestComponent : public IComponent {
    public:
        TestComponent(int a) {
            std::cout << a << std::endl;
        }

        void onCreate() override {
            std::cout << "On Create method" << std::endl;
        }

        void onUpdate(FrameInfo &frameInfo) override {
            static uint32_t frame = 0;
            static uint32_t secondPassed = 0;
            frame++;
            if (frame == 120) {
                secondPassed++;
                std::cout << "On Update method. Second elapsed: " << secondPassed << std::endl;
                frame = 0;
            }
        }

        void onDestroy() override {
            std::cout << "On destroy method" << std::endl;
        }
    };
}


#endif //MINIMINIMOTORWAYS_TESTCOMPONENT_H
