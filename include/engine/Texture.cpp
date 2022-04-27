//
// Created by Jacopo Beragnoli on 27/04/22.
//

#include "Texture.h"

namespace Engine {

    Texture::Texture(const std::shared_ptr<Engine::Model> &model, Pipeline &pipeline) : model(model),
                                                                                        pipeline(pipeline) {}

    Texture::~Texture() {
        destroy(texture);
    }

    void Texture::destroy(TextureInfo texture) {

    }

    void Texture::load() {
        std::string fileName = "../textures/texture.jpg";
    }


}