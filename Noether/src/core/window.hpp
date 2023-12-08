#pragma once

#include "core/defines.hpp"

namespace Noether {
    struct WindowSpec {
        u32 Width;
        u32 Height;
        std::string Title;
    };

    class Window {
        public:
            static std::shared_ptr<Window> Create(const WindowSpec& spec);

            virtual void* GetNativeHandle() = 0;
            virtual ~Window() = default;
            virtual void NewFrame() = 0;
    };
};