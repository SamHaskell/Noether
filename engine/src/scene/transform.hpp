#pragma once

#include "core/defines.hpp"
#include "maths/vector.hpp"
#include "maths/matrix.hpp"

namespace Noether {
    struct Transform {
        Vec3 Position = {0.0f, 0.0f, 0.0f};
        Vec3 Rotation = {0.0f, 0.0f, 0.0f};
        Vec3 Scale = {1.0f, 1.0f, 1.0f};
    
        inline Mat4 LocalTransform() { return Matrix4::Translation(Position) * Matrix4::Rotation(Rotation) * Matrix4::Scale(Scale); }
        inline Vec3 TransformDirection(Vec3 v) { return Vec3(Matrix4::Rotation(Rotation) * Vec4({v.x, v.y, v.z, 0.0f})); }
    };
};