#pragma once

#include "graphics/textures.hpp"
#include "platform/gl/graphicsutils_gl.hpp"

namespace Noether {
    class Texture2DGL : public Texture2D {
        public:
            Texture2DGL(const std::string& path);
            Texture2DGL(i32 width, i32 height, u32 samples = 0, AttachmentType type = AttachmentType::Color);
            ~Texture2DGL();

            inline void Bind(u32 unit = 0) override { 
                glActiveTexture(GL_TEXTURE0 + unit); GL_LOG_ERROR;
                glBindTexture(GL_TEXTURE_2D, m_RendererID); GL_LOG_ERROR;
            }

            inline void Unbind() override { glBindTexture(GL_TEXTURE_2D, 0); GL_LOG_ERROR; }

            inline u32 GetRendererID() { return m_RendererID; }
            inline u32 GetSampleCount() { return m_Samples; }
            
        private:
            u32 m_RendererID;
            u32 m_Samples = 0;
            i32 m_Width;
            i32 m_Height;
            i32 m_Channels;
    };

    class TextureCubeGL : public TextureCube {
        public:
            TextureCubeGL(const CubeMapData& data);
            ~TextureCubeGL();

            inline void Bind() override { 
                glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID); GL_LOG_ERROR;
            }

            inline void Unbind() override { glBindTexture(GL_TEXTURE_CUBE_MAP, 0); GL_LOG_ERROR; }

        private:
            u32 m_RendererID;
            CubeMapData m_Data;
    };
};