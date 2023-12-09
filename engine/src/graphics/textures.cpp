#include "graphics/textures.hpp"
#include "platform/gl/textures_gl.hpp"

namespace Noether {
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
        return std::make_shared<Texture2DGL>(path);
    }

    std::shared_ptr<Texture2D> Texture2D::Create(i32 width, i32 height, u32 samples) {
        return std::make_shared<Texture2DGL>(width, height, samples);
    }

    std::shared_ptr<TextureCube> TextureCube::Create(const CubeMapData& data) {
        return std::make_shared<TextureCubeGL>(data);
    }
};