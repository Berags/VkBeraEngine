//
// Created by Jacopo Beragnoli on 04/05/22.
//

#ifndef MINIMINIMOTORWAYS_ENTITYMANAGER_H
#define MINIMINIMOTORWAYS_ENTITYMANAGER_H

#include <unordered_map>
#include "Entity.h"
#include "../FrameInfo.h"

namespace Engine::ECS {
    class EntityManager {
    public:
        using Map = std::unordered_map<Engine::ECS::Entity::id_t, Engine::ECS::Entity *>;
        static constexpr uint32_t MAX_ENTITIES = 64;

        // Creates a new Entity and adds it to availableEntities Map
        // Checks if number of living entities is greater than MAX_ENTITIES
        // and asserts if true
        template<typename T>
        T createNewEntity() {
            assert(livingEntityCount < Engine::ECS::EntityManager::MAX_ENTITIES && "Too many entities!");

            T entity = Engine::ECS::Entity::create<T>();
            std::cout << "Created entity with id: " << entity.getId() << std::endl;
            availableEntities.emplace(livingEntityCount, &entity);
            livingEntityCount++;
            return entity;
        }

        // Destroys an Entity from availableEntities Map
        // Calls onDestroy method on all Entity components
        // Updates numberOfLivingEntities to match availableEntities size
        void destroyEntity(Engine::ECS::Entity::id_t id);

        // Returns an Entity from a given id
        Engine::ECS::Entity &getEntity(Engine::ECS::Entity::id_t id);

        // Updates all Entities stored in availableEntities
        // i.e. calls method update() on each entity
        void updateEntities(Engine::FrameInfo &frameInfo);

        [[nodiscard]] uint32_t getLivingEntityCount() const;

        [[nodiscard]] const Map &getAvailableEntities() const;

    private:
        // Stores all living Entities
        Engine::ECS::EntityManager::Map availableEntities{};

        // Number of living Entities, should always match availableEntities size
        uint32_t livingEntityCount{};
    };
}


#endif //MINIMINIMOTORWAYS_ENTITYMANAGER_H
