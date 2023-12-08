#pragma once

#include "core/defines.hpp"

namespace Noether {
    class Window {
        public:
            static std::shared_ptr<Window> Create();

            virtual ~Window() = default;
            virtual void NewFrame() = 0;
    };
};