//
// Created by Jacopo Beragnoli on 11/05/22.
//

#ifndef VKBERAENGINE_HEALTHCOMPONENT_H
#define VKBERAENGINE_HEALTHCOMPONENT_H

#include "../../engine/Window.h"
#include "../../engine/GameObject.h"
#include "../../engine/FrameInfo.h"
#include "../../engine/ecs/IComponent.h"

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

#endif //VKBERAENGINE_HEALTHCOMPONENT_H
