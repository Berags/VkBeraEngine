//
// Created by Jacopo Beragnoli on 10/05/22.
//

#ifndef MINIMINIMOTORWAYS_PLAYER_H
#define MINIMINIMOTORWAYS_PLAYER_H

#include "../../engine/Core.h"

namespace Game::Entities {
    class Player : public Engine::ECS::Entity {
    public:
        explicit Player(id_t entityId) : Entity(entityId) {}
    };
}


#endif //MINIMINIMOTORWAYS_PLAYER_H
