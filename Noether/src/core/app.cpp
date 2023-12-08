#include "core/app.hpp"

namespace Noether {
    void App::Run() {

        WindowSpec windowSpec = {
            .Width = 1280,
            .Height = 720,
            .Title = "Noether Application"
        };

        m_Window = Window::Create(windowSpec);
        m_GraphicsDevice = GraphicsDevice::Create(m_Window);

        Initialise();

        m_Running = true;
        m_AppClock.Start();

        while (m_Running) {
            m_Window->NewFrame();
            Tick();
        }

        Shutdown();
    }

    void App::Tick() {
        f64 dt = m_AppClock.Tick();
        
        Update();

        m_GraphicsDevice->Clear();

        Render();

        m_GraphicsDevice->BeginGUI();
        DrawGUI();
        m_GraphicsDevice->EndGUI();
    }
};