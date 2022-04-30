//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_ENTITY_H
#define MINIMINIMOTORWAYS_ENTITY_H

#include <vector>
#include "IComponent.h"

namespace Engine::ECS {
    class Entity {
    public:
        void addComponent(Engine::ECS::IComponent *component);

        void removeComponent(Engine::ECS::IComponent *component);

        void update(float dt);

    private:
        std::vector<Engine::ECS::IComponent *> components;
    };
}


#endif //MINIMINIMOTORWAYS_ENTITY_H
