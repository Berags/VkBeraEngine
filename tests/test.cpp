//
// Created by Jacopo Beragnoli on 13/05/22.
//
#include "../include/engine/Core.h"
#include "../include/game/entities/Player.h"
#include "../include/game/components/HealthComponent.h"
#include "utils.h"
#include "../include/game/entities/Enemy.h"
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>

Engine::ECS::EntityManager entityManager{};

TEST(EntityComponentSystem, EntityManager) {
    ASSERT_EQ(entityManager.getLivingEntityCount(), 0)
                                << "Number of living entity must be 0 when EntityManager is first instantiated!";
    ASSERT_EQ(Engine::ECS::EntityManager::MAX_ENTITIES, 64)
                                << "Max number of entities should be 64!";
    auto entity = entityManager.createNewEntity<Game::Entities::Player>();
    ASSERT_EQ(entityManager.getLivingEntityCount(), 1);
    entityManager.destroyEntity(entity.getId());
    ASSERT_EQ(entityManager.getLivingEntityCount(), 0)
                                << "Number of living entity must be equals to 0 after removing the entity!";
    std::vector<Game::Entities::Enemy> enemies;
    enemies.reserve(10);
    for (int i = 0; i < 10; ++i) {
        enemies[i] = entityManager.createNewEntity<Game::Entities::Enemy>();
        ASSERT_EQ(enemies[i].getId(), i) << "Entity at position " << i << " should have id equals to " << i;
        ASSERT_EQ(entityManager.getLivingEntityCount(), i + 1)
                                    << "Number of created entities must match the living entities count";
    }
}

TEST(EntityComponentSystem, Entity) {
    auto entity = entityManager.createNewEntity<Game::Entities::Player>();
    ASSERT_EQ(entity.getComponents().size(), 0) << "Empty components vector should have size equals to 0!";
    entity.addComponent<Game::Components::HealthComponent>();
    ASSERT_EQ(entity.getComponents().size(), 1)
                                << "Components vector should have size equals to 1 after adding element!";
    auto component = entity.getComponent<Game::Components::HealthComponent>();
    ASSERT_NE(component, nullptr) << "Returned component should not be nullptr!";
    entity.removeComponent<Game::Components::HealthComponent>();
    ASSERT_EQ(entity.getComponents().size(), 0)
                                << "Empty components vector should have size equals to 0 after component removal!";
    component = entity.getComponent<Game::Components::HealthComponent>();
    EXPECT_EQ(component, nullptr) << "Returned component should be nullptr!";
    ASSERT_NO_THROW({
                        entity.addComponent<Game::Components::HealthComponent>();
                        entity.destroy();
                    });
}

TEST(Engine, Exceptions) {
    ASSERT_THROW({
                     try {
                         Tests::Utils::throwException<Engine::Exceptions::UnableToOpenFileException>("quad.obj");
                     } catch (const Engine::Exceptions::UnableToOpenFileException &e) {
                         ASSERT_STREQ("Unable to open selected file! - File Name: quad.obj", e.what());
                         PRINT_STACK_TRACE;
                         throw;
                     } catch (...) {
                         FAIL() << "Expected UnableToOpenFileException!";
                     }
                 }, Engine::Exceptions::UnableToOpenFileException);
    ASSERT_THROW({
                     try {
                         Tests::Utils::throwException<Engine::Exceptions::UnableToStartWindowException>();
                     } catch (const Engine::Exceptions::UnableToStartWindowException &e) {
                         ASSERT_STREQ("Unable to start the GLFW Window!", e.what());
                         PRINT_STACK_TRACE;
                         throw;
                     } catch (...) {
                         FAIL() << "Expected UnableToOpenFileException!";
                     }
                 }, Engine::Exceptions::UnableToStartWindowException);
}