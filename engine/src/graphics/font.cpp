#include "graphics/font.hpp"
#include "platform/gl/font_gl.hpp"

namespace Noether {
    std::shared_ptr<Font> Font::Load(const std::string& path, u32 height) {
        return std::make_shared<FontGL>(path, height);
    }
}