#include "graphics/framebuffer.hpp"
#include "platform/gl/framebuffer_gl.hpp"

namespace Noether {
    std::shared_ptr<FrameBuffer> FrameBuffer::Create(u32 width, u32 height) {
        return std::make_shared<FrameBufferGL>(width, height);
    }
};