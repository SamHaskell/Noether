#pragma once

#include "core/window.hpp"
#include "GLFW/glfw3.h"

namespace Noether {
    class WindowGLFW : public Window {
        public:
            WindowGLFW(const WindowSpec& spec);
            ~WindowGLFW();

            inline void* GetNativeHandle() override { return (void*)m_WindowHandle; };

            void NewFrame() override;
        private:
            GLFWwindow* m_WindowHandle;
    };
}