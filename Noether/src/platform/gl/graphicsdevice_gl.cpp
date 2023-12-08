#include "platform/gl/graphicsdevice_gl.hpp"
#include "platform/gl/graphicsutils_gl.hpp"

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

namespace Noether {
    GraphicsDeviceGL::GraphicsDeviceGL(std::shared_ptr<Window> window) {
        auto windowHandle = (GLFWwindow*)window->GetNativeHandle();

#ifndef PLATFORM_WEB
        gladLoadGL();
#endif

        glfwMakeContextCurrent(windowHandle);

        glEnable(GL_DEPTH_TEST); GL_LOG_ERROR;
        glDepthFunc(GL_LESS); GL_LOG_ERROR;

        glEnable(GL_STENCIL_TEST); GL_LOG_ERROR;
        glStencilMask(0xFF); GL_LOG_ERROR;

        glEnable(GL_CULL_FACE); GL_LOG_ERROR;
        glFrontFace(GL_CCW); GL_LOG_ERROR;
        glCullFace(GL_BACK); GL_LOG_ERROR;

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); GL_LOG_ERROR;

        glClearColor(0.1, 0.1, 0.12, 1.0); GL_LOG_ERROR;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
        ImGui_ImplOpenGL3_Init();

        ImGui::StyleColorsDark();
    }

    void GraphicsDeviceGL::Clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); GL_LOG_ERROR;
    }

    void GraphicsDeviceGL::Clear(ClearFlags flags) const {
        u32 glFlags = 0;
        if (flags & u32(ClearFlagBits::Color)) {
            glFlags |= GL_COLOR_BUFFER_BIT;
        }
        if (flags & u32(ClearFlagBits::Depth)) {
            glFlags |= GL_DEPTH_BUFFER_BIT;
        }
        if (flags & u32(ClearFlagBits::Stencil)) {
            glFlags |= GL_STENCIL_BUFFER_BIT;
        }
        glClear(glFlags); GL_LOG_ERROR;
    }

    void GraphicsDeviceGL::SetDepthTesting(bool isActive) const {
        (isActive) ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE); GL_LOG_ERROR;
    }

    void GraphicsDeviceGL::SetViewportSize(i32 width, i32 height) const {
        glViewport(0, 0, width, height);
    }

    void GraphicsDeviceGL::BeginGUI() const {
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void GraphicsDeviceGL::EndGUI() const {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GraphicsDeviceGL::DrawVertexArray(const std::shared_ptr<VertexArray> va) const {
        va->Bind();
        glDrawElements(GL_TRIANGLES, va->GetIndexCount(), GL_UNSIGNED_INT, (void*)0);
        GL_LOG_ERROR;
    }

    void GraphicsDeviceGL::DrawVertexArray(const std::shared_ptr<VertexArray> va, u32 count) const {
        va->Bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)0);
        GL_LOG_ERROR;
    }
};