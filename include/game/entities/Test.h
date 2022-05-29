//
// Created by Jacopo Beragnoli on 09/05/22.
//

#ifndef VKBERAENGINE_TEST_H
#define VKBERAENGINE_TEST_H

#include "../../engine/ecs/Entity.h"

namespace Game {
    class Test : public Engine::ECS::Entity {
    public:
        explicit Test(id_t id) : Entity(id) {}
    };
}


#endif //VKBERAENGINE_TEST_H
