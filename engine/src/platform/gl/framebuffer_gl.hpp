#pragma once

#include "graphics/framebuffer.hpp"

namespace Noether {
    class FrameBufferGL : public FrameBuffer {
        public:
            FrameBufferGL(u32 width, u32 height, u32 samples);
            ~FrameBufferGL();

            std::shared_ptr<Texture2D> GetColorAttachment() override;

            void Resize(i32 width, i32 height) override;

            void Bind() override;
            void Unbind() override;

            inline u32 GetRendererID() { return m_RendererID; }
        
        private:
            u32 m_RendererID;
            std::shared_ptr<Texture2D> m_ColorAttachment;
            u32 m_DepthAttachment;
    };

    class DepthBufferGL : public DepthBuffer {
        public:
            DepthBufferGL(u32 width, u32 height);
            ~DepthBufferGL();

            void Bind() override;
            void Unbind() override;

            inline u32 GetWidth() override { return m_Width; }
            inline u32 GetHeight() override { return m_Height; }

            inline std::shared_ptr<Texture2D> GetDepthAttachment() override { return m_DepthAttachment; }

            inline u32 GetRendererID() { return m_RendererID; }
        
        private:
            u32 m_RendererID;
            u32 m_Width;
            u32 m_Height;
            std::shared_ptr<Texture2D> m_DepthAttachment;
    };
};