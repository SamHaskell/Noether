#pragma once

#include "core/defines.hpp"

#include "maths/vector.hpp"

namespace Noether {
    struct KeyMod {
        enum Key {
            None            = 0,
            LeftShift       = 1,
            RightShift      = (1 << 1),
            Shift           = LeftShift | RightShift,
            LeftCtrl        = (1 << 2),
            RightCtrl       = (1 << 3),
            Ctrl            = LeftCtrl | RightCtrl,
            LeftAlt         = (1 << 4),
            RightAlt        = (1 << 5),
            Alt             = LeftAlt | RightAlt 
        };
    };

    struct KeyCode {
        enum Key {
            Unknown = 0,

            Return = '\r',
            Escape = '\x1B',
            Backspace = '\b',
            Tab = '\t',
            Space = ' ',
            Exclaim = '!',
            QuoteDouble = '"',
            Hash = '#',
            Percent = '%',
            Dollar = '$',
            Ampersand = '&',
            Quote = '\'',
            LeftParen = '(',
            RightParen = ')',
            Asterisk = '*',
            Plus = '+',
            Comma = ',',
            Minus = '-',
            Period = '.',
            Slash = '/',

            Num0 = '0',
            Num1 = '1',
            Num2 = '2',
            Num3 = '3',
            Num4 = '4',
            Num5 = '5',
            Num6 = '6',
            Num7 = '7',
            Num8 = '8',
            Num9 = '9',

            Colon = ':',
            SemiColon = ';',
            Less = '<',
            Equals = '=',
            Greater = '>',
            Question = '?',
            At = '@',

            LeftBracket = '[',
            Backslash = '\\',
            RightBracket = ']',
            Caret = '^',
            Underscore = '_',
            BackQuote = '`',

            a = 'a',
            b = 'b',
            c = 'c',
            d = 'd',
            e = 'e',
            f = 'f',
            g = 'g',
            h = 'h',
            i = 'i',
            j = 'j',
            k = 'k',
            l = 'l',
            m = 'm',
            n = 'n',
            o = 'o',
            p = 'p',
            q = 'q',
            r = 'r',
            s = 's',
            t = 't',
            u = 'u',
            v = 'v',
            w = 'w',
            x = 'x',
            y = 'y',
            z = 'z',

            CapsLock = 0x40000039,

            F1 = 0x4000003A,
            F2 = 0x4000003B,
            F3 = 0x4000003C,
            F4 = 0x4000003D,
            F5 = 0x4000003E,
            F6 = 0x4000003F,
            F7 = 0x40000040,
            F8 = 0x40000041,
            F9 = 0x40000042,
            F10 = 0x40000043,
            F11 = 0x40000044,
            F12 = 0x40000045,

            LeftCtrl = 0x400000E0,
            LeftShift = 0x400000E1,
            LeftAlt = 0x400000E2,
            LeftGUI = 0x400000E3,
            RightCtrl = 0x400000E4,
            RightShift = 0x400000E5,
            RightAlt = 0x400000E6,
            RightGUI = 0x400000E7,
        };
    };
};