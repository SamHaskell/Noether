#include "graphics/textures.hpp"
#include "platform/gl/textures_gl.hpp"

namespace Noether {
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path, ImageFormat format) {
        return std::make_shared<Texture2DGL>(path, format);
    }

    std::shared_ptr<Texture2D> Texture2D::Create(i32 width, i32 height, u32 samples, AttachmentType type) {
        return std::make_shared<Texture2DGL>(width, height, samples, type);
    }

    std::shared_ptr<TextureCube> TextureCube::Create(const CubeMapData& data) {
        return std::make_shared<TextureCubeGL>(data);
    }
};