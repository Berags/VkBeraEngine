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
        // Template args taken from:
        // https://stackoverflow.com/questions/35587654/candidate-function-not-viable-expects-an-l-value-for-3rd-argument
        template<typename T, typename ... Ts>
        void addComponent(Ts &... args) {
            T *component = new T(args...);
            bool isAlreadyInComponents = false;
            std::for_each(components.begin(), components.end(), [&](const auto &item) {
                if (Engine::Utils::instanceof<T>(item)) isAlreadyInComponents = true;
            });
            if (!isAlreadyInComponents) {
                // component not in components, add it
                components.push_back(component);
                component->onCreate();
            }
        }

        // Removes a component to the Entity components vector
        // Checks if the component is actually stored
        template<typename T>
        void removeComponent() {
            components.erase(
                    std::remove_if(
                            components.begin(),
                            components.end(),
                            [](auto &component) {
                                return Engine::Utils::instanceof<T>(component);
                            }
                    ));
        }

        // Updates all the components stored into components vector
        // Calls onUpdate on each component stored into components vector
        void update(Engine::FrameInfo &frameInfo);

        // Destroys the Entity
        // Calls onDestroy on each component stored into components vector
        void destroy();

        [[nodiscard]] id_t getId() const;

        [[nodiscard]] const std::vector<Engine::ECS::IComponent *> &getComponents() const;

    protected:
        // Available only by its subclasses
        explicit Entity(id_t entityId);

    private:
        id_t id;
        std::vector<Engine::ECS::IComponent *> components;
    };
}


#endif //MINIMINIMOTORWAYS_ENTITY_H
