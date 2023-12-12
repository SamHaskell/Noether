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

        const char* path = "assets/fonts/NotoSans/NotoSans.ttf";
        FT_Face face;
        if (FT_New_Face(ft, path.c_str(), 0, &face)) {
            NT_ERROR("Could not load font from file: %s", path.c_str());
        }

        // face, width, height. setting width to zero will let it be autocalculated.
        FT_Set_Pixel_Sizes(face, 0, 48);

        for (u8 c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                NT_ERROR("Failed to load glyph!");
            }
        }
    }

    FontGL::~FontGL() {

    }
};