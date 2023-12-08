#include "maths/vector.hpp"
#include "maths/maths.hpp"

namespace Noether {
    namespace Vector2 {
        f32 SqrMagnitude(const Vec2& v) {
            return (v.x*v.x) + (v.y*v.y);
        }

        f32 Magnitude(const Vec2& v) {
            return sqrtf(SqrMagnitude(v));
        }

        Vec2 Normalised(const Vec2& v) {
            f32 normalisation = 1.0f / Magnitude(v);
            return {v.x * normalisation, v.y * normalisation};
        }

        f32 Dot(const Vec2& u, const Vec2& v) {
            return (u.x*v.x) + (u.y*v.y);
        }

        Vec2 Hadamard(const Vec2& u, const Vec2& v) {
            return {u.x * v.x, u.y * v.y};
        }

        Vec2 Lerp(const Vec2& u, const Vec2& v, f32 t) {
            return {Maths::Lerp(u.x, v.x, t), Maths::Lerp(u.y, v.y, t)};
        }

        Vec2 LerpClamped(const Vec2& u, const Vec2& v, f32 t) {
            return {Maths::LerpClamped(u.x, v.x, t), Maths::LerpClamped(u.y, v.y, t)};
        }
    };

    namespace Vector3 {
        f32 SqrMagnitude(const Vec3& v) {
            return (v.x*v.x) + (v.y*v.y) + (v.z*v.z);
        }

        f32 Magnitude(const Vec3& v) {
            return sqrtf(SqrMagnitude(v));
        }

        Vec3 Normalised(const Vec3& v) {
            f32 normalisation = 1.0f / Magnitude(v);
            return {v.x * normalisation, v.y * normalisation, v.z * normalisation};
        }

        f32 Dot(const Vec3& u, const Vec3& v) {
            return (u.x*v.x) + (u.y*v.y) + (u.z*v.z);
        }

        Vec3 Hadamard(const Vec3& u, const Vec3& v) {
            return {u.x * v.x, u.y * v.y, u.z * v.z};
        }

        Vec3 Lerp(const Vec3& u, const Vec3& v, f32 t) {
            return {Maths::Lerp(u.x, v.x, t), Maths::Lerp(u.y, v.y, t), Maths::Lerp(u.z, v.z, t)};
        }

        Vec3 LerpClamped(const Vec3& u, const Vec3& v, f32 t) {
            return {Maths::LerpClamped(u.x, v.x, t), Maths::LerpClamped(u.y, v.y, t), Maths::LerpClamped(u.z, v.z, t)};
        }

        Vec3 Cross(const Vec3& u, const Vec3& v) {
            return {
                u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x
            };
        }
    };
};