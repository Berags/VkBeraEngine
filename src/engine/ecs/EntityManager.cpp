//
// Created by Jacopo Beragnoli on 04/05/22.
//

#include "../../../include/engine/ecs/EntityManager.h"

namespace Engine::ECS {
    Engine::ECS::Entity EntityManager::createNewEntity() {
        assert(livingEntityCount < Engine::ECS::EntityManager::MAX_ENTITIES && "Too many entities!");

        auto entity = Engine::ECS::Entity::create();
        availableEntities.emplace(livingEntityCount, entity);
        livingEntityCount++;
        return entity;
    }

    void EntityManager::destroyEntity(Engine::ECS::Entity::id_t id) {
        assert(id < Engine::ECS::EntityManager::MAX_ENTITIES && "Entity out of range!");

        availableEntities.at(id).destroy();
        availableEntities.erase(id);
        livingEntityCount--;
    }

    Engine::ECS::Entity &EntityManager::getEntity(Engine::ECS::Entity::id_t id) {
        assert(id < Engine::ECS::EntityManager::MAX_ENTITIES && "Entity out of range!");

        return availableEntities.at(id);
    }

    void EntityManager::updateEntities(Engine::FrameInfo &frameInfo) {
        std::for_each(availableEntities.begin(), availableEntities.end(), [&](auto &item) {
            auto &entity = item.second;
            entity.update(frameInfo.frameTime);
        });
    }
}