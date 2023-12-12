#pragma once

#include "noether.hpp"

namespace Noether {
    class Template : public App {
        public:
            Template() = default;
            ~Template() = default;

            void Initialise() override;
            void Shutdown() override;

            void Update(f64 dt) override;
            void Render() override;
            void DrawGUI() override;
            void OnEvent(Event& e) override;
    };
};