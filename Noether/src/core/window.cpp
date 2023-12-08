#include "core/window.hpp"
#include "platform/glfw/window_glfw.hpp"

namespace Noether {
    std::shared_ptr<Window> Window::Create() {
        return std::make_shared<WindowGLFW>();
    }
}
