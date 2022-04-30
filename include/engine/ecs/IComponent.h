//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_ICOMPONENT_H
#define MINIMINIMOTORWAYS_ICOMPONENT_H

namespace Engine::ECS {
    class IComponent {
    public:
        virtual void onUpdate(float dt) = 0;
    };
}


#endif //MINIMINIMOTORWAYS_ICOMPONENT_H
