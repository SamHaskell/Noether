#pragma once

#include "core/window.hpp"
#include "GLFW/glfw3.h"

namespace Noether {
    class WindowGLFW : public Window {
        public:
            WindowGLFW();
            ~WindowGLFW();

            void NewFrame() override;
        private:
            GLFWwindow* m_WindowHandle;
    };
}