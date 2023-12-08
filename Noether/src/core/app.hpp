#pragma once

#include "core/clock.hpp"

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
            bool m_Running;
            Clock m_AppClock;

            void Tick();

    };
};