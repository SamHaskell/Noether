#include "core/app.hpp"

#include "core/input.hpp"

namespace Noether {
    void App::Run() {

        WindowSpec windowSpec = {
            .Width = 1280,
            .Height = 720,
            .Title = "Noether Application",
            .EventCallback = std::bind(&App::HandleEvent, this, std::placeholders::_1),
            .Mode = DisplayMode::Windowed
        };

        m_Window = Window::Create(windowSpec);
        Input::SetInputSource(m_Window);
        m_GraphicsDevice = GraphicsDevice::Create(m_Window);

        Initialise();

        m_Running = true;
        m_AppClock.Start();

        while (m_Running) {
            Tick();
        }

        Shutdown();
    }

    void App::HandleEvent(Event& e) {
        switch (e.Type) {
            case Event::Type::WindowClose:
            {
                m_Running = false;
                e.Handled = true;
                break;
            }
            case Event::Type::WindowBackbufferSize:
            {
                m_GraphicsDevice->SetViewport(e.WindowBackbufferSize.Width, e.WindowBackbufferSize.Height);
            }
            default:
                break;
        }

        if (!e.Handled) {
            OnEvent(e);
        }
    }

    void App::Tick() {
        f64 dt = m_AppClock.Tick();
        m_Window->NewFrame();
        
        Update(dt);

        m_GraphicsDevice->Clear();
        {
            Render();

            m_GraphicsDevice->BeginGUI();
            {
                DrawGUI();
            }
            m_GraphicsDevice->EndGUI();
        }
    }
};