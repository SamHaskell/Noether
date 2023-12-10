#pragma once

#include "core/defines.hpp"

namespace Noether {
    struct Vec2;
    struct Vec3;
    struct Vec4;

    struct Vec2 {
        f32 x;
        f32 y;

        bool operator==(const Vec2& other) const { return (x == other.x) && (y == other.y); }

        void operator*=(const f32 val) { x *= val; y *= val; }
        void operator*=(const Vec2& v) { x *= v.x; y *= v.y; }
        Vec2 operator* (const f32 val) const { return { x * val, y * val }; }
        Vec2 operator* (const Vec2& v) const { return { x * v.x, y * v.y }; }
        void operator+=(const f32 val) { x += val; y += val; }
        void operator+=(const Vec2& v) { x += v.x; y += v.y; }
        Vec2 operator+ (const f32 val) const { return { x + val, y + val }; }
        Vec2 operator+ (const Vec2& v) const { return { x + v.x, y + v.y }; }
        void operator-=(const f32 val) { x -= val; y -= val; }
        void operator-=(const Vec2& v) { x -= v.x; y -= v.y; }
        Vec2 operator- (const f32 val) const { return { x - val, y - val }; }
        Vec2 operator- (const Vec2& v) const { return { x - v.x, y - v.y }; }

        inline void AddScaledVector(const Vec2& vec, f32 scale) {
            x += vec.x * scale;
            y += vec.y * scale;
        }
        
        inline void HadamardInPlace(const Vec2& other) {
            x *= other.x;
            y *= other.y;
        }

        inline void NormaliseInPlace() {
            f32 inv = 1.0f/sqrtf(x*x + y*y);
            x *= inv;
            y *= inv;
        }
    };
    
    inline Vec2 operator- (const Vec2& v) { return {-v.x, -v.y}; }
    
    namespace Vector2 {
        inline Vec2 Up() { return {0.0, 1.0}; }
        inline Vec2 Down() { return {0.0, -1.0}; }
        inline Vec2 Right() { return {1.0, 0.0}; }
        inline Vec2 Left() { return {-1.0, 0.0}; }

        f32 SqrMagnitude(const Vec2& v);
        f32 Magnitude(const Vec2& v);
        Vec2 Normalised(const Vec2& v);
        f32 Dot(const Vec2& u, const Vec2& v);
        Vec2 Hadamard(const Vec2& u, const Vec2& v);
        Vec2 Lerp(const Vec2& u, const Vec2& v, f32 t);
        Vec2 LerpClamped(const Vec2& u, const Vec2& v, f32 t);
    };

    struct Vec4 {
        union {
            struct {
                f32 x;
                f32 y;
                f32 z;
                f32 w;
            };
            struct {
                f32 r;
                f32 g;
                f32 b;
                f32 a;
            };
        };
    };

    using Color = Vec4;

    struct Vec3 {
        Vec3() = default;
        Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {};
        Vec3(Vec4 v) : x(v.x), y(v.y), z(v.z) {}

        f32 x;
        f32 y;
        f32 z;

        bool operator==(const Vec3& other) const { return (x == other.x) && (y == other.y) && (z == other.z); }

        void operator*=(const f32 val) { x *= val; y *= val; z *= val; }
        void operator*=(const Vec3& v) { x *= v.x; y *= v.y; z *= v.z; }
        Vec3 operator* (const f32 val) const { return { x * val, y * val, z * val }; }
        Vec3 operator* (const Vec3& v) const { return { x * v.x, y * v.y, z * v.z }; }
        void operator+=(const f32 val) { x += val; y += val; z += val; }
        void operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; }
        Vec3 operator+ (const f32 val) const { return { x + val, y + val, z + val }; }
        Vec3 operator+ (const Vec3& v) const { return { x + v.x, y + v.y, z + v.z }; }
        void operator-=(const f32 val) { x -= val; y -= val; z -= val; }
        void operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; }
        Vec3 operator- (const f32 val) const { return { x - val, y - val, z - val }; }
        Vec3 operator- (const Vec3& v) const { return { x - v.x, y - v.y, z - v.z }; }

        inline void AddScaledVector(const Vec3& vec, f32 scale) {
            x += vec.x * scale;
            y += vec.y * scale;
            z += vec.z * scale;
        }
        
        inline void HadamardInPlace(const Vec3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
        }

        inline void NormaliseInPlace() {
            f32 inv = 1.0f/sqrtf(x*x + y*y + z*z);
            x *= inv;
            y *= inv;
            z *= inv;
        }
    };

    inline Vec3 operator- (const Vec3& v) { return {-v.x, -v.y, -v.z}; }

    namespace Vector3 {
        inline Vec3 Up() { return {0.0, 1.0, 0.0}; }
        inline Vec3 Down() { return {0.0, -1.0, 0.0}; }
        inline Vec3 Right() { return {1.0, 0.0, 0.0}; }
        inline Vec3 Left() { return {-1.0, 0.0, 0.0}; }
        inline Vec3 Forward() { return {0.0, 0.0, -1.0}; }
        inline Vec3 Back() { return {0.0, 0.0, 1.0}; }

        f32 SqrMagnitude(const Vec3& v);
        f32 Magnitude(const Vec3& v);
        Vec3 Normalised(const Vec3& v);
        f32 Dot(const Vec3& u, const Vec3& v);
        Vec3 Hadamard(const Vec3& u, const Vec3& v);
        Vec3 Lerp(const Vec3& u, const Vec3& v, f32 t);
        Vec3 LerpClamped(const Vec3& u, const Vec3& v, f32 t);
        Vec3 Cross(const Vec3& u, const Vec3& v);
        Vec3 DirectionFromEuler(const Vec3& v);
    };
};

namespace std {
    template<> struct hash<Noether::Vec3> {
        size_t operator()(Noether::Vec3 const& v) const {
            return ((hash<f32>()(v.x) ^
                   (hash<f32>()(v.y) << 1)) >> 1) ^
                   (hash<f32>()(v.z) << 1);
        }
    };

    template<> struct hash<Noether::Vec2> {
        size_t operator()(Noether::Vec2 const& v) const {
            return ((hash<f32>()(v.x) ^
                   (hash<f32>()(v.y) << 1)) >> 1);
        }
    };
}