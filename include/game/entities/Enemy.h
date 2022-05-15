//
// Created by Jacopo Beragnoli on 12/05/22.
//

#ifndef MINIMINIMOTORWAYS_ENEMY_H
#define MINIMINIMOTORWAYS_ENEMY_H

#include "../../engine/Core.h"

namespace Game::Entities {
    class Enemy : public Engine::ECS::Entity {
    public:
        explicit Enemy(id_t id) : Entity(id) {}
    };
} // Game::Entities

#endif //MINIMINIMOTORWAYS_ENEMY_H
