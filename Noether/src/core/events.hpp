#pragma once

#include "core/defines.hpp"
#include "core/input.hpp"

namespace Noether {
    struct KeyEvent
    {
        KeyCode::Key Key;
        KeyMod::Key Mod;
        bool IsDown;
    };

    struct MouseMovementEvent
    {
        f64 X;
        f64 Y;
    };

    struct WindowCloseEvent
    {
        
    };

    struct WindowBackbufferSizeEvent
    {
        i32 Width;
        i32 Height;
    };

    struct WindowSizeEvent
    {
        i32 Width;
        i32 Height;
    };

    struct Event {
        enum class Type {
            Key,
            MouseButton,
            MouseMovement,
            WindowClose,
            WindowBackbufferSize,
            WindowSize
        };

        Type Type;
        bool Handled = false;

        union {
            KeyEvent KeyPress;
            MouseMovementEvent MouseMovement;
            WindowCloseEvent WindowClose;
            WindowBackbufferSizeEvent WindowBackbufferSize;
            WindowSizeEvent WindowSize;
        };
        
    };
};