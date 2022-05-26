//
// Created by Jacopo Beragnoli on 11/05/22.
//

#ifndef MINIMINIMOTORWAYS_GAMEOBJECTCOMPONENT_H
#define MINIMINIMOTORWAYS_GAMEOBJECTCOMPONENT_H

#include "../../engine/Window.h"
#include "../../engine/GameObject.h"
#include "../../engine/FrameInfo.h"
#include "../../engine/ecs/IComponent.h"

namespace Game::Components {
    class GameObjectComponent : public Engine::ECS::IComponent {
    public:
        GameObjectComponent(Engine::GameObject &gameObject) : gameObject(gameObject) {}

        void onCreate() override {
            std::cout << "Created GameObjectComponent" << std::endl;
        }

        void onUpdate(Engine::FrameInfo &frameInfo) override {
            static uint32_t frame = 0;
            static uint32_t secondPassed = 0;
            frame++;
            if (frame == 120) {
                secondPassed++;
                frame = 0;
            }
        }

        void onDestroy() override {
            std::cout << "On destroy method" << std::endl;
        }

    private:
        Engine::GameObject &gameObject;
    };
}


#endif //MINIMINIMOTORWAYS_GAMEOBJECTCOMPONENT_H
