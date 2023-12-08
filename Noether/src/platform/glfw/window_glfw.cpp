#include "platform/glfw/window_glfw.hpp"

static bool s_GLFWInitialised = false;
static bool s_FrameInProgress = false;

namespace Noether {
    WindowGLFW::WindowGLFW() {
        if (!s_GLFWInitialised) {
            i32 init_ok = glfwInit();
            NT_ASSERT(init_ok == GLFW_TRUE, "GLFW failed to initialise.");
        }

#ifdef PLATFORM_MAC
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        m_WindowHandle = glfwCreateWindow(
            1280, 720,
            "Noether Application",
            NULL, NULL
        );

        glfwMakeContextCurrent(m_WindowHandle);
    }

    WindowGLFW::~WindowGLFW() {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }
    
    void WindowGLFW::NewFrame() {
        glfwSwapBuffers(m_WindowHandle);
        glfwPollEvents();
    }
}