#include "platform/gl/textures_gl.hpp"

#include "stb_image.h"

namespace Noether {
    Texture2DGL::Texture2DGL(const std::string& path) {
        glGenTextures(1, &m_RendererID); GL_LOG_ERROR;
        glBindTexture(GL_TEXTURE_2D, m_RendererID); GL_LOG_ERROR;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); GL_LOG_ERROR;

        stbi_set_flip_vertically_on_load(true);
        u8* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4); GL_LOG_ERROR;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); GL_LOG_ERROR;
        glGenerateMipmap(GL_TEXTURE_2D); GL_LOG_ERROR;
        stbi_image_free(data);
    }

    Texture2DGL::Texture2DGL(i32 width, i32 height) {
        m_Width = width;
        m_Height = height;
        m_Channels = 4;
    
        glGenTextures(1, &m_RendererID); GL_LOG_ERROR;
        glBindTexture(GL_TEXTURE_2D, m_RendererID); GL_LOG_ERROR;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GL_LOG_ERROR;

        glBindTexture(GL_TEXTURE_2D, 0); GL_LOG_ERROR;
    }

    Texture2DGL::~Texture2DGL() {
        
    }

    TextureCubeGL::TextureCubeGL(const CubeMapData& data) : m_Data(data) {
        glGenTextures(1, &m_RendererID); GL_LOG_ERROR;
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID); GL_LOG_ERROR;

        i32 width, height, channels;
        u8* imageData;
        stbi_set_flip_vertically_on_load(false);
        for (i32 i = 0; i < 6; i++) {
            imageData = stbi_load(data.Paths[i].c_str(), &width, &height, &channels, 4);
            if (imageData) {
                glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData
                ); GL_LOG_ERROR;
                stbi_image_free(imageData);
            } else {
                NT_ERROR("Failed to load cubemap texture at %s", data.Paths[i].c_str());
                stbi_image_free(imageData);
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); GL_LOG_ERROR;
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); GL_LOG_ERROR;
    }
    
    TextureCubeGL::~TextureCubeGL() {

    }
}