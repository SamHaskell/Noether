#include "core/app.hpp"

namespace Noether {
    void App::Run() {
        Initialise();

        m_Running = true;
        m_AppClock.Start();

        while (m_Running) {
            Tick();
        }

        Shutdown();
    }

    void App::Tick() {
        f64 dt = m_AppClock.Tick();

        Update();

        Render();

        DrawGUI();
    }
};