//
// Created by Jacopo Beragnoli on 09/05/22.
//

#ifndef MINIMINIMOTORWAYS_TEST_H
#define MINIMINIMOTORWAYS_TEST_H

#include "../../engine/ecs/Entity.h"

namespace Game {
    class Test : public Engine::ECS::Entity {
    public:
        explicit Test(id_t id) : Entity(id) {}
    };
}


#endif //MINIMINIMOTORWAYS_TEST_H
