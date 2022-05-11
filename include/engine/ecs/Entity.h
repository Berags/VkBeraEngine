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
        template<typename T>
        static T create() {
            static id_t currentId = 0;
            return T{currentId++};
        }

        // Adds a component to the Entity components vector
        // Checks if the same component is already stored
        template<typename T, typename ... Ts>
        void addComponent(Ts &... args) {
            T *component = new T(args...);
            if (std::find(components.begin(), components.end(), component) == components.end()) {
                // component not in components, add it
                components.push_back(component);
                component->onCreate();
            }
        }

        // Removes a component to the Entity components vector
        // Checks if the component is actually stored
        void removeComponent(Engine::ECS::IComponent *component);

        // Updates all the components stored into components vector
        // Calls onUpdate on each component stored into components vector
        void update(Engine::FrameInfo &frameInfo);

        // Destroys the Entity
        // Calls onDestroy on each component stored into components vector
        void destroy();

        [[nodiscard]] id_t getId() const;

        [[nodiscard]] const std::vector<Engine::ECS::IComponent *> &getComponents() const;

    protected:
        // Available only by its sub classes
        explicit Entity(id_t entityId);

    private:
        id_t id;
        std::vector<Engine::ECS::IComponent *> components;
    };
}


#endif //MINIMINIMOTORWAYS_ENTITY_H
