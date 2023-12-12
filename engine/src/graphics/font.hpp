#pragma once

#include "core/defines.hpp"

namespace Noether {
    class Font {
        public:
            static std::shared_ptr<Font> Load(const std::string& path, u32 height);
    };
};