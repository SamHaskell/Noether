#pragma once

#include "core/clock.hpp"
#include "core/window.hpp"
#include "graphics/graphicsdevice.hpp"

namespace Noether {
    class App {
        public:
            App() = default;
            virtual ~App() = default;

            void Run();

            virtual void Initialise() = 0;
            virtual void Shutdown() = 0;

            virtual void Update() = 0;
            virtual void Render() = 0;
            virtual void DrawGUI() = 0;
            virtual void OnEvent() = 0;

        private:
            std::shared_ptr<Window> m_Window;
            std::shared_ptr<GraphicsDevice> m_GraphicsDevice;

            bool m_Running;
            Clock m_AppClock;

            void Tick();

    };
};