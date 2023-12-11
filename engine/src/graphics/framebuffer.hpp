#pragma once

#include "core/defines.hpp"
#include "graphics/textures.hpp"

namespace Noether {
    class FrameBuffer {
        public:
            static std::shared_ptr<FrameBuffer> Create(u32 width, u32 height, u32 samples);
            virtual ~FrameBuffer() = default;

            virtual std::shared_ptr<Texture2D> GetColorAttachment() = 0;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual void Resize(i32 width, i32 height) = 0;
    };

    class DepthBuffer {
        public:
            static std::shared_ptr<DepthBuffer> Create(u32 width, u32 height);
            virtual ~DepthBuffer() = default;

            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual std::shared_ptr<Texture2D> GetDepthAttachment() = 0;

            virtual u32 GetWidth() = 0;
            virtual u32 GetHeight() = 0;
    };
};