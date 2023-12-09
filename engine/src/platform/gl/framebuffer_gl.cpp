#include "platform/gl/framebuffer_gl.hpp"
#include "platform/gl/graphicsutils_gl.hpp"
#include "platform/gl/textures_gl.hpp"

namespace Noether {
    FrameBufferGL::FrameBufferGL(u32 width, u32 height, u32 samples = 0) {
        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

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

    DepthBufferGL::DepthBufferGL(u32 width, u32 height) {
        glGenFramebuffers(1, &m_RendererID);

        m_DepthAttachment = Texture2D::Create(width, height, 0, AttachmentType::Depth);

        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            std::static_pointer_cast<Texture2DGL>(m_DepthAttachment)->GetRendererID(),
            0
        );
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    DepthBufferGL::~DepthBufferGL() {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void DepthBufferGL::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void DepthBufferGL::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};