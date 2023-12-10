#pragma once

#include "core/defines.hpp"
#include "graphics/mesh.hpp"

namespace Noether {
    namespace Shapes {
        std::shared_ptr<Mesh> CreateSphere(f32 radius = 1.0f, u32 sectors = 36, u32 stacks = 18);
    };
};