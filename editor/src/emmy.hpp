#pragma once

#include "noether.hpp"

namespace Noether {
    class Editor : public App {
        public:
            Editor() = default;
            ~Editor() = default;

            void Initialise() override;
            void Shutdown() override;

            void Update() override;
            void Render() override;
            void DrawGUI() override;
            void OnEvent(Event& e) override;
    };
};