//
// Created by Jacopo Beragnoli on 04/05/22.
//

// includes
#include "../../../include/engine/ecs/EntityManager.h"

namespace Engine::ECS {
    void EntityManager::destroyEntity(Engine::ECS::Entity::id_t id) {
        assert(id < Engine::ECS::EntityManager::MAX_ENTITIES && "Entity out of range!");

        availableEntities.at(id)->destroy();
        availableEntities.erase(id);
        livingEntityCount--;
    }

    Engine::ECS::Entity &EntityManager::getEntity(Engine::ECS::Entity::id_t id) {
        assert(id < Engine::ECS::EntityManager::MAX_ENTITIES && "Entity out of range!");

        return *availableEntities.at(id);
    }

    void EntityManager::updateEntities(Engine::FrameInfo &frameInfo) {
        for (auto &kv: availableEntities) {
            auto &entity = kv.second;
            entity->update(frameInfo);
        }
    }

    uint32_t EntityManager::getLivingEntityCount() const {
        return livingEntityCount;
    }

    const EntityManager::Map &EntityManager::getAvailableEntities() const {
        return availableEntities;
    }
}