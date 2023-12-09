#pragma once

#include "core/defines.hpp"
#include "core/events.hpp"

namespace Noether {
    enum class DisplayMode {
        Windowed,
        WindowedFullscreen,
        Fullscreen
    };

    struct WindowSpec {
        u32 Width = 600;
        u32 Height = 800;
        std::string Title = "Noether Application";
        std::function<void(Event&)> EventCallback;
        DisplayMode Mode = DisplayMode::WindowedFullscreen;
    };

    class Window {
        public:
            static std::shared_ptr<Window> Create(const WindowSpec& spec);

            virtual void* GetNativeHandle() = 0;
            virtual ~Window() = default;
            virtual void NewFrame() = 0;
    };
};