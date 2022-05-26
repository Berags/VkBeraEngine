//
// Created by Jacopo Beragnoli on 30/04/22.
//

// includes
#include "../include/engine/ecs/Entity.h"

namespace Engine::ECS {
    void Entity::update(Engine::FrameInfo &frameInfo) {
        for (auto &component: components) {
            component->onUpdate(frameInfo);
        }
    }

    id_t Entity::getId() const {
        return id;
    }

    void Entity::destroy() {
        std::for_each(components.begin(), components.end(), [&](const auto &item) {
            item->onDestroy();
            free(item);
        });
        components.clear();
    }

    const std::vector<Engine::ECS::IComponent *> &Entity::getComponents() const {
        return components;
    }

    Entity::~Entity() {
        std::cout << "Destroying entity" << std::endl;
    }
}

