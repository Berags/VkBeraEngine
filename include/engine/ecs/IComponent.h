//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef VKBERAENGINE_ICOMPONENT_H
#define VKBERAENGINE_ICOMPONENT_H

#include <cmath>
#include "../FrameInfo.h"

namespace Engine::ECS {
    class IComponent {
    public:
        // On Create Method
        // Is called when a Component is created and added to an Entity
        virtual void onCreate() = 0;

        // On Update Method
        // Is called on each frame and updates the Component related to an Entity
        virtual void onUpdate(Engine::FrameInfo &frameInfo) = 0;

        // On Destroy Method
        // Is called whenever a Component is removed from an Entity or whenever an
        // Entity is destroyed
        virtual void onDestroy() = 0;
    };
}


#endif //VKBERAENGINE_ICOMPONENT_H
