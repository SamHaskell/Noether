#pragma once

#include "graphics/font.hpp"
#include <map>

namespace Noether {
    struct Glyph {
        u32 RendererID;
        u32 Width;
        u32 Height;
        u32 BearingX;
        u32 BearingY;
        u32 Advance;
    };

    class FontGL : public Font {
        public:
            FontGL(const std::string& path, u32 height);
            ~FontGL();

        private:
            std::map<i8, Glyph> m_Glyphs;
    };
}