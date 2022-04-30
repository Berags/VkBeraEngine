//
// Created by Jacopo Beragnoli on 30/04/22.
//
#include "../include/engine/ecs/Entity.h"

namespace Engine::ECS {

    void Entity::addComponent(Engine::ECS::IComponent *component) {
        if (std::find(components.begin(), components.end(), component) == components.end()) {
            // component not in name, add it
            components.push_back(component);
        }
    }

    void Entity::removeComponent(Engine::ECS::IComponent *component) {
        auto it = std::find(components.begin(), components.end(), component);
        if (it != components.end()) { components.erase(it); }
    }

    void Entity::update(float dt) {
        std::for_each(components.begin(), components.end(), [&](const auto &item) {
            item->onUpdate(dt);
        });
    }
}

