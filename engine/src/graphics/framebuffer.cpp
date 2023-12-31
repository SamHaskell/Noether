#include "graphics/framebuffer.hpp"
#include "platform/gl/framebuffer_gl.hpp"

namespace Noether {
    std::shared_ptr<FrameBuffer> FrameBuffer::Create(u32 width, u32 height, u32 samples) {
        return std::make_shared<FrameBufferGL>(width, height, samples);
    }

    std::shared_ptr<DepthBuffer> DepthBuffer::Create(u32 width, u32 height) {
        return std::make_shared<DepthBufferGL>(width, height);
    }
};