//
// Created by Jacopo Beragnoli on 12/05/22.
//

#ifndef MINIMINIMOTORWAYS_SCENE_H
#define MINIMINIMOTORWAYS_SCENE_H

#include "GameObject.h"

namespace Engine {
    class Scene {
    public:
        static void load(GameObject::Map &gameObjects, Engine::Device &device);

        static void loadTextures(TextureStorage &textureStorage);
    };
}


#endif //MINIMINIMOTORWAYS_SCENE_H
