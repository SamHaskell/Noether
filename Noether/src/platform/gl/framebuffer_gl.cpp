#include "platform/gl/framebuffer_gl.hpp"
#include "platform/gl/graphicsutils_gl.hpp"
#include "platform/gl/textures_gl.hpp"

namespace Noether {
    FrameBufferGL::FrameBufferGL(u32 width, u32 height, u32 samples = 0) {
        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        // To complete a framebuffer we need:
        //  - At least one buffer (color, depth, stencil)
        //  - At least one color attachment
        //  - All attachments should have some reserved memory on GPU
        //  - Each buffer should have the same number of samples

        m_ColorAttachment = Texture2D::Create(width, height, samples);

        GLenum target = (samples == 0) ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE;

        glFramebufferTexture2D(
            GL_FRAMEBUFFER, 
            GL_COLOR_ATTACHMENT0, 
            target, 
            std::static_pointer_cast<Texture2DGL>(m_ColorAttachment)->GetRendererID(), 
            0
        ); GL_LOG_ERROR;

        glGenRenderbuffers(1, &m_DepthAttachment); GL_LOG_ERROR;
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment); GL_LOG_ERROR;

        if (samples == 0) {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); GL_LOG_ERROR;
        } else {
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height); GL_LOG_ERROR;
        }
        
        glBindRenderbuffer(GL_RENDERBUFFER, 0); GL_LOG_ERROR;

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment); GL_LOG_ERROR;

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            NT_ERROR("Framebuffer is not complete!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0); GL_LOG_ERROR;
    }

    FrameBufferGL::~FrameBufferGL() {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    std::shared_ptr<Texture2D> FrameBufferGL::GetColorAttachment() {
        return m_ColorAttachment;
    }

    void FrameBufferGL::Resize(i32 width, i32 height) {
        glDeleteFramebuffers(1, &m_RendererID);

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        // To complete a framebuffer we need:
        //  - At least one buffer (color, depth, stencil)
        //  - At least one color attachment
        //  - All attachments should have some reserved memory on GPU
        //  - Each buffer should have the same number of samples

        m_ColorAttachment = Texture2D::Create(width, height);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER, 
            GL_COLOR_ATTACHMENT0, 
            GL_TEXTURE_2D, 
            std::static_pointer_cast<Texture2DGL>(m_ColorAttachment)->GetRendererID(), 
            0
        ); GL_LOG_ERROR;

        glGenRenderbuffers(1, &m_DepthAttachment); GL_LOG_ERROR;
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment); GL_LOG_ERROR;
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); GL_LOG_ERROR;
        glBindRenderbuffer(GL_RENDERBUFFER, 0); GL_LOG_ERROR;

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment); GL_LOG_ERROR;

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            NT_ERROR("Framebuffer is not complete!");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0); GL_LOG_ERROR;
    }

    void FrameBufferGL::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void FrameBufferGL::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};