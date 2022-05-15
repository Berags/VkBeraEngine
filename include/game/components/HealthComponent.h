//
// Created by Jacopo Beragnoli on 11/05/22.
//

#ifndef MINIMINIMOTORWAYS_HEALTHCOMPONENT_H
#define MINIMINIMOTORWAYS_HEALTHCOMPONENT_H

#include "../../engine/Core.h"

namespace Game::Components {
    class HealthComponent : public Engine::ECS::IComponent {
    public:
        explicit HealthComponent(uint32_t health = 100) : health(health) {}

        void onCreate() override {
            std::cout << "Attached health component with Health Value: " << health << std::endl;
        }

        void onUpdate(Engine::FrameInfo &frameInfo) override {}

        void onDestroy() override {}

    private:
        uint32_t health;
    };
} // Game::Components

#endif //MINIMINIMOTORWAYS_HEALTHCOMPONENT_H
