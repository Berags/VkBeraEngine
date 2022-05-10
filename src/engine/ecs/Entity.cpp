//
// Created by Jacopo Beragnoli on 30/04/22.
//

// includes
#include "../include/engine/ecs/Entity.h"

namespace Engine::ECS {

    void Entity::removeComponent(Engine::ECS::IComponent *component) {
        auto it = std::find(components.begin(), components.end(), component);
        if (it != components.end()) { components.erase(it); }
    }

    void Entity::update(Engine::FrameInfo &frameInfo) {
        for (auto &component: components) {
            component->onUpdate(frameInfo);
        }
    }

    Entity::Entity(id_t entityId) : id(entityId) {}

    id_t Entity::getId() const {
        return id;
    }

    void Entity::destroy() {
        std::for_each(components.begin(), components.end(), [&](const auto &item) {
            item->onDestroy();
        });
    }

    const std::vector<Engine::ECS::IComponent *> &Entity::getComponents() const {
        return components;
    }
}

