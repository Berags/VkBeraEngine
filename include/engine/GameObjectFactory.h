//
// Created by Jacopo Beragnoli on 15/05/22.
//

#ifndef MINIMINIMOTORWAYS_GAMEOBJECTFACTORY_H
#define MINIMINIMOTORWAYS_GAMEOBJECTFACTORY_H

#include "GameObject.h"

namespace Engine {
    class GameObjectFactory {
    public:
        // Factory method that create a generic game object with a unique identifier
        static Engine::GameObject createGameObject(const char *name) {
            static GameObject::id_t currentId = 0;
            return GameObject{currentId++, name};
        }

        // Factory method that create a billboard point light
        static Engine::GameObject createPointLight(float intensity = 10.f,
                                                   float radius = .1f,
                                                   glm::vec3 color = glm::vec3(1.f)) {
            GameObject gameObject = createGameObject("Point Light");
            gameObject.color = color;
            gameObject.transform.scale.x = radius;
            gameObject.pointLightComponent = std::make_unique<Engine::PointLightComponent>();
            gameObject.pointLightComponent->lightIntensity = intensity;
            return gameObject;
        }
    };
}
#endif //MINIMINIMOTORWAYS_GAMEOBJECTFACTORY_H
