//
// Created by Jacopo Beragnoli on 30/04/22.
//

#ifndef MINIMINIMOTORWAYS_ICOMPONENT_H
#define MINIMINIMOTORWAYS_ICOMPONENT_H

#include <cmath>

namespace Engine::ECS {
    class IComponent {
    public:
        virtual void onCreate() = 0; // Only called one time when dt == 0

        virtual void onUpdate(float dt) {
            if (equals(dt, .0f)) onCreate();
        }

    private:
        static bool equals(float a, float b) {
            return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * std::numeric_limits<double>::epsilon());
        }
    };
}


#endif //MINIMINIMOTORWAYS_ICOMPONENT_H
