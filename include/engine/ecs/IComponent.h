//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_ICOMPONENT_H
#define MINIMINIMOTORWAYS_ICOMPONENT_H

#include <cmath>

namespace Engine::ECS {
    class IComponent {
    public:
        // On Create Method
        // Is called when a Component is created and added to an Entity
        virtual void onCreate() = 0;

        // On Update Method
        // Is called on each frame and updates the Component related to an Entity
        virtual void onUpdate(float dt) = 0;

        // On Destroy Method
        // Is called whenever a Component is removed from an Entity or whenever an
        // Entity is destroyed
        virtual void onDestroy() = 0;
    };
}


#endif //MINIMINIMOTORWAYS_ICOMPONENT_H
