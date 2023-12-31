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
            void HandleEvent(Event& e);

            virtual void Initialise() = 0;
            virtual void Shutdown() = 0;

            virtual void Update(f64 dt) = 0;
            virtual void Render() = 0;
            virtual void DrawGUI() = 0;
            virtual void OnEvent(Event& e) = 0;

            inline const std::shared_ptr<Window> GetMainWindow() { return m_Window; }
            inline const std::shared_ptr<GraphicsDevice> GetGraphicsDevice() { return m_GraphicsDevice; }

        private:
            std::shared_ptr<Window> m_Window;
            std::shared_ptr<GraphicsDevice> m_GraphicsDevice;

            bool m_Running;
            Clock m_AppClock;

            void Tick();

    };
};