#pragma once

#include "core/defines.hpp"
#include "core/window.hpp"
#include "graphics/buffers.hpp"

namespace Noether {
    using ClearFlags = u32;
    enum class ClearFlagBits {
        Color = 1,
        Depth = (1 << 1),
        Stencil = (1 << 2),
    };

    class GraphicsDevice {
        public:
            static std::shared_ptr<GraphicsDevice> Create(std::shared_ptr<Window> window);
            ~GraphicsDevice() = default;

            virtual void Clear() const = 0;
            virtual void Clear(ClearFlags flags) const = 0;

            virtual void SetDepthTesting(bool isActive) const = 0;
            virtual void SetViewport(i32 width, i32 height) const = 0;
            virtual void SetVSync(bool isActive) const = 0;

            virtual void BeginGUI() const = 0;
            virtual void EndGUI() const = 0;

            virtual void DrawVertexArray(const std::shared_ptr<VertexArray> va) const = 0;
            virtual void DrawVertexArray(const std::shared_ptr<VertexArray> va, u32 count) const = 0;

    };
};