#pragma once

#include "core/window.hpp"
#include "GLFW/glfw3.h"

namespace Noether {
    struct WindowStateGLFW {
        i32 Width;
        i32 Height;
        i32 BackbufferWidth;
        i32 BackbufferHeight;
        std::function<void(Event&)> EventCallback;
    };

    class WindowGLFW : public Window {
        public:
            WindowGLFW(const WindowSpec& spec);
            ~WindowGLFW();

            inline i32 GetScreenWidth() override { return m_WindowState.Width; }
            inline i32 GetScreenHeight() override { return m_WindowState.Height; }
            inline i32 GetBackbufferWidth() override { return m_WindowState.BackbufferWidth; }
            inline i32 GetBackbufferHeight() override { return m_WindowState.BackbufferHeight; }

            inline void* GetNativeHandle() override { return (void*)m_WindowHandle; };

            void NewFrame() override;
        private:
            GLFWwindow* m_WindowHandle;
            WindowStateGLFW m_WindowState;
    };
}