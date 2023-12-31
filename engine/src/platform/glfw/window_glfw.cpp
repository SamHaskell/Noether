#include "platform/glfw/window_glfw.hpp"

static bool s_GLFWInitialised = false;

namespace Noether {

    static void glfw_window_close_callback(GLFWwindow* window);
    static void glfw_key_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
    static void glfw_mouse_button_callback(GLFWwindow* window, i32 button, i32 action, i32 mods);
    static void glfw_mouse_move_callback(GLFWwindow* window, f64 xpos, f64 ypos);
    static void glfw_window_size_callback(GLFWwindow* window, i32 width, i32 height);
    static void glfw_backbuffer_size_callback(GLFWwindow* window, i32 width, i32 height);

    WindowGLFW::WindowGLFW(const WindowSpec& spec) {
        if (!s_GLFWInitialised) {
            i32 init_ok = glfwInit();
            NT_ASSERT(init_ok == GLFW_TRUE, "GLFW failed to initialise.");
        }

#ifdef PLATFORM_MAC
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        auto monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        i32 chosenWidth, chosenHeight;
        GLFWmonitor* chosenMonitor = NULL;

        switch (spec.Mode) {
            case DisplayMode::Windowed:
                chosenWidth = spec.Width;
                chosenHeight = spec.Height;
                glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
                break;
            case DisplayMode::WindowedFullscreen:
                chosenWidth = mode->width;
                chosenHeight = mode->height;
                glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
                break;
            case DisplayMode::Fullscreen:
                chosenMonitor = monitor;
                break;
        }

        m_WindowHandle = glfwCreateWindow(
            chosenWidth, chosenHeight,
            spec.Title.c_str(),
            chosenMonitor, NULL
        );

        NT_ASSERT(m_WindowHandle != NULL, "GLFW Failed to create a Window!");

        glfwGetWindowSize(m_WindowHandle, &m_WindowState.Width, &m_WindowState.Height);
        glfwGetFramebufferSize(m_WindowHandle, &m_WindowState.BackbufferWidth, &m_WindowState.BackbufferHeight);
        m_WindowState.EventCallback = spec.EventCallback;

        glfwSetWindowUserPointer(m_WindowHandle, &m_WindowState);

        glfwSetWindowCloseCallback(m_WindowHandle, glfw_window_close_callback);
        glfwSetKeyCallback(m_WindowHandle, glfw_key_callback);
        glfwSetMouseButtonCallback(m_WindowHandle, glfw_mouse_button_callback);
        glfwSetCursorPosCallback(m_WindowHandle, glfw_mouse_move_callback);
        glfwSetWindowSizeCallback(m_WindowHandle, glfw_window_size_callback);
        glfwSetFramebufferSizeCallback(m_WindowHandle, glfw_backbuffer_size_callback);
    }

    WindowGLFW::~WindowGLFW() {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }
    
    void WindowGLFW::NewFrame() {
        glfwSwapBuffers(m_WindowHandle);
        glfwPollEvents();
    }

    static void glfw_window_close_callback(GLFWwindow* window) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        Event e = {
            .Type = Event::Type::WindowClose
        };
        state->EventCallback(e);
    }

    static void glfw_key_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        Event e = {
            .Type = Event::Type::Key,
            .KeyPress = {
                .Key = KeyCode(key),
                .Mods = mods,
                .IsDown = (action == GLFW_RELEASE) ? false : true,
                .IsRepeat = (action == GLFW_REPEAT) ? true : false
            }
        };
        state->EventCallback(e);
    }

    static void glfw_mouse_button_callback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        Event e = {
            .Type = Event::Type::MouseButton,
            .MouseButton = {
                .Button = MouseButton(button),
                .Mods = mods,
                .IsDown = (action == GLFW_RELEASE) ? false : true
            }
        };
        state->EventCallback(e);
    }

    static void glfw_mouse_move_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        Event e = {
            .Type = Event::Type::MouseMovement,
            .MouseMovement = {
                .X = xpos,
                .Y = ypos
            }
        };
        state->EventCallback(e);
    }

    static void glfw_window_size_callback(GLFWwindow* window, i32 width, i32 height) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        state->Width = width;
        state->Height = height;
        Event e = {
            .Type = Event::Type::WindowSize,
            .WindowSize = {
                .Width = width,
                .Height = height
            }
        };
        state->EventCallback(e);
    }

    static void glfw_backbuffer_size_callback(GLFWwindow* window, i32 width, i32 height) {
        auto state = (WindowStateGLFW*)glfwGetWindowUserPointer(window);
        state->BackbufferWidth = width;
        state->BackbufferHeight = height;
        Event e = {
            .Type = Event::Type::WindowBackbufferSize,
            .WindowBackbufferSize = {
                .Width = width,
                .Height = height
            }
        };
        state->EventCallback(e);
    }
}