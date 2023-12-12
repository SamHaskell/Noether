#pragma once

#include "graphics/font.hpp"
#include <map>

namespace Noether {
    struct Glyph {
        u32 RendererID;
        i32 Width;
        i32 Height;
        i32 BearingX;
        i32 BearingY;
        u32 Advance;
    };

    class FontGL : public Font {
        public:
            FontGL(const std::string& path, u32 height);

        private:
            std::map<i8, Glyph> m_Glyphs;
    };
}