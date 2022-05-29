//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef VKBERAENGINE_ENTITY_H
#define VKBERAENGINE_ENTITY_H

#include <vector>
#include "IComponent.h"

namespace Engine::ECS {
    class Entity {
    public:
        using id_t = uint32_t;

        explicit Entity(id_t id) : id(id) {}

        virtual ~Entity();

        // Adds a component to the Entity components vector
        // Checks if the same component is already stored
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

        // Returns a pointer to the component of Type T if is inside
        // of components vector
        template<typename T>
        T *getComponent() {
            for (auto &component: components) {
                if (Engine::Utils::instanceof<T>(component)) return dynamic_cast<T *>(component);
            }
            return nullptr;
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

    private:
        id_t id;
        std::vector<Engine::ECS::IComponent *> components;
    };
}


#endif //VKBERAENGINE_ENTITY_H
