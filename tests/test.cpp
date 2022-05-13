//
// Created by Jacopo Beragnoli on 13/05/22.
//
#include "../include/engine/ecs/EntityManager.h"
#include "../include/game/entities/Player.h"
#include <gtest/gtest.h>

TEST(EntityComponentSystem, EntityManager) {
    Engine::ECS::EntityManager entityManager{};
    ASSERT_EQ(entityManager.getLivingEntityCount(), 0)
                        << "Number of living entity should be 0 when EntityManager is first instantiated!";
    ASSERT_EQ(Engine::ECS::EntityManager::MAX_ENTITIES, 64)
                        << "Max number of entities should be 64!";
    entityManager.createNewEntity<Game::Entities::Player>();
    ASSERT_EQ(entityManager.getLivingEntityCount(), 1);
}