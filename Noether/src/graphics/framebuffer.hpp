#pragma once

#include "core/defines.hpp"
#include "graphics/textures.hpp"

namespace Noether {
    class FrameBuffer {
        public:
            static std::shared_ptr<FrameBuffer> Create(u32 width, u32 height);
            virtual ~FrameBuffer() = default;

            virtual std::shared_ptr<Texture2D> GetColorAttachment() = 0;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual void Resize(i32 width, i32 height) = 0;
    };
};