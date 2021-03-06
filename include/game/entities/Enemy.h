//
// Created by Jacopo Beragnoli on 12/05/22.
//

#ifndef VKBERAENGINE_ENEMY_H
#define VKBERAENGINE_ENEMY_H

#include "../../engine/ecs/Entity.h"

namespace Game::Entities {
    class Enemy : public Engine::ECS::Entity {
    public:
        explicit Enemy(id_t id) : Entity(id) {}
    };
} // Game::Entities

#endif //VKBERAENGINE_ENEMY_H
