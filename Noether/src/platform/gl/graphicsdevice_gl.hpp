#pragma once

#include "core/window.hpp"
#include "graphics/graphicsdevice.hpp"

namespace Noether {
    class GraphicsDeviceGL : public GraphicsDevice {
        public:
            GraphicsDeviceGL(std::shared_ptr<Window> window);
            ~GraphicsDeviceGL() = default;
            
            void Clear() const override;
            void Clear(ClearFlags flags) const override;

            void SetDepthTesting(bool isActive) const override;
            void SetViewport(i32 width, i32 height) const override;

            void BeginGUI() const override;
            void EndGUI() const override;
        
            void DrawVertexArray(const std::shared_ptr<VertexArray> va) const override;
            void DrawVertexArray(const std::shared_ptr<VertexArray> va, u32 count) const override;
    };
};