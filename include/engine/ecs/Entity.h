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
        using id_t = unsigned int;

        Entity() = delete;

        static Entity create() {
            static id_t currentId = 0;
            return Entity{currentId++};
        }

        void addComponent(Engine::ECS::IComponent *component);

        void removeComponent(Engine::ECS::IComponent *component);

        void update(float dt);

        [[nodiscard]] id_t getId() const;

    private:
        id_t id;
        std::vector<Engine::ECS::IComponent *> components;

        explicit Entity(id_t entityId);
    };
}


#endif //MINIMINIMOTORWAYS_ENTITY_H
