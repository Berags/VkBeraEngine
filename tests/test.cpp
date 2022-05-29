//
// Created by Jacopo Beragnoli on 13/05/22.
//
#include "../include/game/entities/Player.h"
#include "../include/engine/exceptions/Exception.h"
#include "../include/game/components/HealthComponent.h"
#include "utils.h"
#include "../include/game/entities/Enemy.h"
#include "../include/engine/ecs/EntityManager.h"
#include "../include/engine/exceptions/file/FailedToLoadFileException.h"
#include <gtest/gtest.h>

constexpr uint16_t width = 800;
constexpr uint16_t height = 600;
Engine::Window window{"Test Window", width, height};
Engine::Device device{window};
Engine::TextureStorage textureStorage{device};

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
    for (int i = 0; i < 10; ++i) {
        auto enemy = entityManager.createNewEntity<Game::Entities::Enemy>();
        ASSERT_EQ(enemy.getId(), i) << "Entity at position " << i << " should have id equals to " << i;
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
    ASSERT_EQ(typeid(Game::Components::HealthComponent *), typeid(component))
                                << "Returned component must have selected Object Type!";
    entity.removeComponent<Game::Components::HealthComponent>();
    ASSERT_EQ(entity.getComponents().size(), 0)
                                << "Empty components vector should have size equals to 0 after component removal!";
    component = entity.getComponent<Game::Components::HealthComponent>();
    EXPECT_EQ(component, nullptr) << "Returned component should be nullptr!";
    ASSERT_NO_THROW({
                        entity.addComponent<Game::Components::HealthComponent>();
                        entity.destroy();
                    });
    ASSERT_EXIT({
                    component = entity.getComponent<Game::Components::HealthComponent>();
                    component->onCreate();
                }, testing::KilledBySignal(SIGSEGV), "^$")
                                << "Destroyed entity's component should be nullptr!\nCalling method from a nullptr\n";
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
                         Tests::Utils::throwException<Engine::Exceptions::FailedToCreateVkObject>("Pipeline Layout");
                     } catch (const Engine::Exceptions::FailedToCreateVkObject &e) {
                         ASSERT_STREQ("Failed to create Vulkan Object: Pipeline Layout", e.what());
                         PRINT_STACK_TRACE;
                         throw;
                     } catch (...) {
                         FAIL() << "Expected UnableToStartWindowException!";
                     }
                 }, Engine::Exceptions::FailedToCreateVkObject);
    ASSERT_THROW({
                     try {
                         Tests::Utils::throwException<Engine::Exceptions::UnableToStartWindowException>();
                     } catch (const Engine::Exceptions::UnableToStartWindowException &e) {
                         ASSERT_STREQ("Unable to start the GLFW Window!", e.what());
                         PRINT_STACK_TRACE;
                         throw;
                     } catch (...) {
                         FAIL() << "Expected UnableToStartWindowException!";
                     }
                 }, Engine::Exceptions::UnableToStartWindowException);
}

TEST(Engine, Vulkan) {
    uint32_t version = 0;
    auto vkEnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion) vkGetInstanceProcAddr(
            nullptr, "vkEnumerateInstanceVersion");

    ASSERT_NE(vkEnumerateInstanceVersion, nullptr) << "Vulkan was unable to enumerate current SDK Version!";
    vkEnumerateInstanceVersion(&version);
    std::cout << "Vulkan Version: (" << version << ") " << VK_VERSION_MAJOR(version) << "." << VK_VERSION_MINOR(version)
              << "." << VK_VERSION_PATCH(version) << "\n";
}

TEST(Engine, Window) {
    std::cout << "Testing window dimensions\n";
    EXPECT_EQ(window.getWidth(), width) << "Window should have width equals to " << width << "!\n";
    EXPECT_EQ(window.getHeight(), height) << "Window should have height equals to " << height << "!\n";

    ASSERT_NE(window.getGlfwWindow(), nullptr) << "GLFW Window must not be nullptr while window is active!\n";

    glfwPollEvents();
}

TEST(Engine, Device) {
    ASSERT_NE(device.getVkDevice(), nullptr) << "VkDevice (i.e. Physical Device) must not be nullptr!\n";
    EXPECT_EQ(device.getGraphicsQueueFamily(), 0) << "Get Graphics Queue Family should be equals to 0!\n";
    ASSERT_NE(device.getInstance(), nullptr) << "VkInstance must not be nullptr!\n";
}

TEST(Engine, Texture) {
    ASSERT_NO_THROW({
                        textureStorage.loadTexture("../../textures/texture.jpg", "statue");
                        textureStorage.loadTexture("../../textures/viking_room.png", "viking_room");
                        textureStorage.loadTexture("../../textures/high_resolution.jpg", "high_resolution");
                    });
    ASSERT_THROW({
                     try {
                         textureStorage.loadTexture("Fake Path", "statue");
                     } catch (const Engine::Exceptions::FailedToLoadFileException &e) {
                         ASSERT_STREQ("Unable to load selected file! - File Path: Fake Path", e.what());
                         std::cerr << e.what() << std::endl;
                         PRINT_STACK_TRACE;
                         throw;
                     } catch (...) {
                         FAIL() << "Expected FailedToLoadFileException!";
                     }
                 }, Engine::Exceptions::FailedToLoadFileException);
}

int main(int argc, char **argv) {
    // Called if an exception occurs before starting tests
    // (e.g. Error while instantiating Window, Device, TextureStorage)
    std::set_terminate([]() -> void {
        std::cerr << "Terminate called after throwing an instance of ";
        try {
            std::rethrow_exception(std::current_exception());
        }
        catch (const std::exception &ex) {
            std::cerr << typeid(ex).name() << std::endl;
            std::cerr << "\n  what(): " << ex.what() << std::endl;
        }
        catch (...) {
            std::cerr << typeid(std::current_exception()).name() << std::endl;
            std::cerr << " ... not an exception." << std::endl;
        }
        std::cerr << "errno: " << errno << ": " << std::strerror(errno) << std::endl;
        std::abort();
    });
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}