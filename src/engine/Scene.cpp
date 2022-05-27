//
// Created by Jacopo Beragnoli on 12/05/22.
//

#include "../../include/engine/Scene.h"
#include "../../include/engine/GameObjectFactory.h"

namespace Engine {
    void Scene::load(Engine::GameObject::Map &gameObjects, Engine::Device &device) {
        std::ifstream i("../json/game_state.json");
        json j;
        i >> j;
        for (auto &it: j) {
            std::cout << "Loading model: ";
            if (it["model"]["file_name"].is_null()) {
                // Light
                std::cout << "light\n";
                auto pointLight = Engine::GameObjectFactory::createPointLight(it["intensity"].get<float>());
                pointLight.name = it["name"].get<std::string>();
                pointLight.color = glm::vec3(it["transform"]["color"]["x"].get<float>(),
                                             it["transform"]["color"]["y"].get<float>(),
                                             it["transform"]["color"]["z"].get<float>());
                pointLight.transform.translation = glm::vec3(it["transform"]["translation"]["x"].get<float>(),
                                                             it["transform"]["translation"]["y"].get<float>(),
                                                             it["transform"]["translation"]["z"].get<float>());
                pointLight.transform.scale = glm::vec3(it["transform"]["scale"]["x"].get<float>(),
                                                       it["transform"]["scale"]["y"].get<float>(),
                                                       it["transform"]["scale"]["z"].get<float>());
                gameObjects.emplace(pointLight.getId(), std::move(pointLight));
            } else {
                // Object
                std::cout << "Object\n";
                std::shared_ptr<Engine::Model> model = Engine::Model::createModelFromFile(device,
                                                                                          it["model"]["file_name"].get<std::string>().c_str());
                std::string name = it["model"]["file_name"].get<std::string>().substr(10);
                auto obj = Engine::GameObjectFactory::createGameObject(name.c_str());
                obj.model = model;
                obj.name = it["name"].get<std::string>();
                obj.color = glm::vec3(it["transform"]["color"]["x"].get<float>(),
                                      it["transform"]["color"]["y"].get<float>(),
                                      it["transform"]["color"]["z"].get<float>());
                obj.transform.translation = glm::vec3(it["transform"]["translation"]["x"].get<float>(),
                                                      it["transform"]["translation"]["y"].get<float>(),
                                                      it["transform"]["translation"]["z"].get<float>());
                obj.transform.scale = glm::vec3(it["transform"]["scale"]["x"].get<float>(),
                                                it["transform"]["scale"]["y"].get<float>(),
                                                it["transform"]["scale"]["z"].get<float>());
                obj.transform.rotation = glm::vec3(it["transform"]["rotation"]["x"].get<float>(),
                                                   it["transform"]["rotation"]["y"].get<float>(),
                                                   it["transform"]["rotation"]["z"].get<float>());
                obj.model->setTextureName(it["model"]["texture"].get<std::string>());
                gameObjects.emplace(obj.getId(), std::move(obj));
            }
        }
    }

    void Scene::loadTextures(TextureStorage &textureStorage) {
        textureStorage.loadTexture("../textures/texture.jpg", "statue");
        textureStorage.loadTexture("../textures/viking_room.png", "viking_room");
        textureStorage.loadTexture("../textures/high_resolution.jpg", "high_resolution");
    }
}