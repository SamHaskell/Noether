#pragma once

#include "core/defines.hpp"
#include "maths/vector.hpp"

namespace Noether {
    struct Mat2 {
        f32 data[4];
    
        inline f32 operator[](size_t pos) const { return data[pos]; }
        inline f32& operator[](size_t pos) { return data[pos]; }
    };

    struct Mat3 {
        f32 data[9];

        inline f32 operator[](size_t pos) const { return data[pos]; }
        inline f32& operator[](size_t pos) { return data[pos]; }
    };

    struct Mat4 {
        f32 data[16];

        inline f32 operator[](size_t pos) const { return data[pos]; }
        inline f32& operator[](size_t pos) { return data[pos]; }

        void operator*=(const f32& val);
        void operator*=(const Mat4& other);
        Mat4 operator* (const f32 val) const;
        Vec4 operator* (const Vec4& other) const;
        Mat4 operator* (const Mat4& other) const;
        void operator+=(const f32 val);
        void operator+=(const Mat4& other);
        Mat4 operator+ (const f32 val) const;
        Mat4 operator+ (const Mat4& other) const;
        void operator-=(const f32 val);
        void operator-=(const Mat4& other);
        Mat4 operator- (const f32 val) const;
        Mat4 operator- (const Mat4& other) const;

        void Rotate(Vec3 euler);
        void Rotate(f32 x, f32 y, f32 z);
    };

    namespace Matrix4 {
        Mat4 Identity();

        Mat4 Translation(Vec3 displacement);
        Mat4 Translation(f32 x, f32 y, f32 z);

        // Order of rotations is Roll -> Yaw -> Pitch (Z -> Y -> X)
        Mat4 Rotation(Vec3 euler);
        Mat4 Rotation(f32 x, f32 y, f32 z);

        Mat4 Scale(Vec3 scale);
        Mat4 Scale(f32 x, f32 y, f32 z);

        Mat4 ViewLookDir(Vec3 position, Vec3 forward, Vec3 up = {0.0f, 1.0f, 0.0f});
        Mat4 ViewLookAt(Vec3 position, Vec3 target, Vec3 up = {0.0f, 1.0f, 0.0f});
        Mat4 Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
        Mat4 Perspective(f32 fovyInDeg, f32 aspect, f32 near, f32 far);
    };
};