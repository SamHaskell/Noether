#pragma once

#include "core/defines.hpp"
#include "maths/vector.hpp"

namespace Noether {
    struct PointLight {
        Color AmbientColor = {1.0f, 1.0f, 1.0f, 1.0f};
        f32 AmbientIntensity = 0.1f;
        Color Color = {1.0f, 1.0f, 1.0f, 1.0f};
        Vec3 Position = {0.0f, 0.0f, 0.0f};
        f32 ConstantAttenuation = 1.0f;
        f32 LinearAttenuation = 0.7f;
        f32 QuadraticAttenuation = 1.8f;
    };

    struct DirectionalLight {
        Color AmbientColor = {1.0f, 1.0f, 1.0f, 1.0f};
        f32 AmbientIntensity = 0.1f;
        Color Color = {1.0f, 1.0f, 1.0f, 1.0f};
        f32 Intensity = 0.3f;
        Vec3 Direction = {0.0f, -0.4f, -1.0f};
    };
};