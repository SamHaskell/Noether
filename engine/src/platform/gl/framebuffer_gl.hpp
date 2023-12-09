#pragma once

#include "graphics/framebuffer.hpp"

namespace Noether {
    class FrameBufferGL : public FrameBuffer {
        public:
            FrameBufferGL(u32 width, u32 height, u32 samples);
            ~FrameBufferGL();

            virtual std::shared_ptr<Texture2D> GetColorAttachment() override;

            virtual void Resize(i32 width, i32 height) override;

            virtual void Bind() override;
            virtual void Unbind() override;

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

            virtual void Bind() override;
            virtual void Unbind() override;

            inline u32 GetRendererID() { return m_RendererID; }
        
        private:
            u32 m_RendererID;
            std::shared_ptr<Texture2D> m_DepthAttachment;
    };
};