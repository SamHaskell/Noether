#include "platform/gl/font_gl.hpp"

#include "platform/gl/graphicsutils_gl.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Noether {
    FontGL::FontGL(const std::string& path, u32 height) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            NT_ERROR("Could not initialise FreeType.");
        }

        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face)) {
            NT_ERROR("Could not load font from file: %s", path.c_str());
        }

        // face, width, height. setting width to zero will let it be autocalculated.
        FT_Set_Pixel_Sizes(face, 0, height);


        // Need to implement atlasing, this is obviously terrible for now.
        for (u8 c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                NT_ERROR("Failed to load glyph!");
            }

            Glyph glyph = {
                .Width      = static_cast<u32>(face->glyph->bitmap.width),
                .Height     = static_cast<u32>(face->glyph->bitmap.rows),
                .BearingX   = static_cast<u32>(face->glyph->bitmap_left),
                .BearingY   = static_cast<u32>(face->glyph->bitmap_top),
                .Advance    = static_cast<u32>(face->glyph->advance.x)
            };

            glGenTextures(1, &glyph.RendererID);
            glBindTexture(GL_TEXTURE_2D, glyph.RendererID);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                static_cast<u32>(face->glyph->bitmap.width),
                static_cast<u32>(face->glyph->bitmap.rows),
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            m_Glyphs.insert(std::pair<i8, Glyph>(c, glyph));
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    FontGL::~FontGL() {

    }
};