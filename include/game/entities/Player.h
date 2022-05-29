//
// Created by Jacopo Beragnoli on 10/05/22.
//

#ifndef VKBERAENGINE_PLAYER_H
#define VKBERAENGINE_PLAYER_H

#include "../../engine/ecs/Entity.h"

namespace Game::Entities {
    class Player : public Engine::ECS::Entity {
    public:
        explicit Player(id_t id) : Entity(id) {}
    };
}


#endif //VKBERAENGINE_PLAYER_H
