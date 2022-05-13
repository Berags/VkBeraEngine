//
// Created by Jacopo Beragnoli on 13/05/22.
//
#include "../include/engine/Core.h"
#include "../include/game/entities/Player.h"
#include <gtest/gtest.h>

TEST(EntityComponentSystem, EntityManager) {
    Engine::ECS::EntityManager entityManager{};
    ASSERT_EQ(entityManager.getLivingEntityCount(), 0)
                                << "Number of living entity must be 0 when EntityManager is first instantiated!";
    ASSERT_EQ(Engine::ECS::EntityManager::MAX_ENTITIES, 64)
                                << "Max number of entities should be 64!";
    auto entity = entityManager.createNewEntity<Game::Entities::Player>();
    ASSERT_EQ(entityManager.getLivingEntityCount(), 1);
    EXPECT_EQ(entity.getId(), 0) << "First created entity should have id equals to 0!";
    ASSERT_EQ(entity.getComponents().size(), 0) << "Empty components vector should have size equals to 0!";
}