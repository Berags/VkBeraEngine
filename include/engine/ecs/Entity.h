//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_ENTITY_H
#define MINIMINIMOTORWAYS_ENTITY_H

#include <vector>
#include "IComponent.h"

namespace Engine::ECS {
    class Entity {
    public:
        using id_t = uint32_t;

        // Explicitly deleted public constructor so that an Entity
        // can only be created from its Factory Method
        Entity() = delete;

        // Entity Factory Method
        // Generates its own id
        static Entity create() {
            static id_t currentId = 0;
            return Entity{currentId++};
        }

        // Adds a component to the Entity components vector
        // Checks if the same component is already stored
        void addComponent(Engine::ECS::IComponent *component);

        // Removes a component to the Entity components vector
        // Checks if the component is actually stored
        void removeComponent(Engine::ECS::IComponent *component);

        // Updates all the components stored into components vector
        // Calls onUpdate on each component stored into components vector
        void update(float dt);

        // Destroys the Entity
        // Calls onDestroy on each component stored into components vector
        void destroy();

        [[nodiscard]] id_t getId() const;

    private:
        id_t id;
        std::vector<Engine::ECS::IComponent *> components;

        explicit Entity(id_t entityId);
    };
}


#endif //MINIMINIMOTORWAYS_ENTITY_H
