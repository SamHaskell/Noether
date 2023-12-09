#include "core/input.hpp"

#include "core/window.hpp"
#include "GLFW/glfw3.h"

namespace Noether {
    std::shared_ptr<Window> Input::m_Owner;

    bool Input::IsKeyPressed(KeyCode key) {
        auto* window = m_Owner->GetNativeHandle();
        return glfwGetKey((GLFWwindow*)window, (i32)key) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseButton button) {
        auto* window = m_Owner->GetNativeHandle();
        return glfwGetMouseButton((GLFWwindow*)window, (i32)button) == GLFW_PRESS;
    }
    
    Vec2 Input::GetMousePosition() {
        auto* window = m_Owner->GetNativeHandle();

        f64 x, y;
        glfwGetCursorPos((GLFWwindow*)window, &x, &y);
        return {(f32)x, (f32)y};
    }
};