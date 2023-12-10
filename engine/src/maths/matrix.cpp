#include "maths/matrix.hpp"

namespace Noether {

    void Mat4::operator*=(const f32& val) {
        data[0] *= val; data[1] *= val; data[2] *= val; data[3] *= val;
        data[4] *= val; data[5] *= val; data[6] *= val; data[7] *= val;
        data[8] *= val; data[9] *= val; data[10] *= val; data[11] *= val;
        data[12] *= val; data[13] *= val; data[14] *= val; data[15] *= val;
    }

    void Mat4::operator*=(const Mat4& other) {
        (*this) = (*this) * other;
    }

    Mat4 Mat4::operator* (const f32 val) const {
        return {
            data[0] * val, data[1] * val, data[2] * val, data[3] * val,
            data[4] * val, data[5] * val, data[6] * val, data[7] * val,
            data[8] * val, data[9] * val, data[10] * val, data[11] * val,
            data[12] * val, data[13] * val, data[14] * val, data[15] * val
        };
    }

    Vec4 Mat4::operator* (const Vec4& other) const {
        return {
            data[0] * other.x + data[4] * other.y + data[8] * other.z + data[12] * other.w,
            data[1] * other.x + data[5] * other.y + data[9] * other.z + data[13] * other.w,
            data[2] * other.x + data[6] * other.y + data[10] * other.z + data[14] * other.w,
            data[3] * other.x + data[7] * other.y + data[11] * other.z + data[15] * other.w
        };
    }

    Mat4 Mat4::operator* (const Mat4& other) const {
        return {
            data[0] * other[0] + data[4] * other[1] + data[8] * other[2] + data[12] * other[3],
            data[1] * other[0] + data[5] * other[1] + data[9] * other[2] + data[13] * other[3],
            data[2] * other[0] + data[6] * other[1] + data[10] * other[2] + data[14] * other[3],
            data[3] * other[0] + data[7] * other[1] + data[11] * other[2] + data[15] * other[3],

            data[0] * other[4] + data[4] * other[5] + data[8] * other[6] + data[12] * other[7],
            data[1] * other[4] + data[5] * other[5] + data[9] * other[6] + data[13] * other[7],
            data[2] * other[4] + data[6] * other[5] + data[10] * other[6] + data[14] * other[7],
            data[3] * other[4] + data[7] * other[5] + data[11] * other[6] + data[15] * other[7],

            data[0] * other[8] + data[4] * other[9] + data[8] * other[10] + data[12] * other[11],
            data[1] * other[8] + data[5] * other[9] + data[9] * other[10] + data[13] * other[11],
            data[2] * other[8] + data[6] * other[9] + data[10] * other[10] + data[14] * other[11],
            data[3] * other[8] + data[7] * other[9] + data[11] * other[10] + data[15] * other[11],

            data[0] * other[12] + data[4] * other[13] + data[8] * other[14] + data[12] * other[15],
            data[1] * other[12] + data[5] * other[13] + data[9] * other[14] + data[13] * other[15],
            data[2] * other[12] + data[6] * other[13] + data[10] * other[14] + data[14] * other[15],
            data[3] * other[12] + data[7] * other[13] + data[11] * other[14] + data[15] * other[15]
        };
    }

    void Mat4::operator+=(const f32 val) {
        data[0] += val; data[1] += val; data[2] += val; data[3] += val;
        data[4] += val; data[5] += val; data[6] += val; data[7] += val;
        data[8] += val; data[9] += val; data[10] += val; data[11] += val;
        data[12] += val; data[13] += val; data[14] += val; data[15] += val;
    }

    void Mat4::operator+=(const Mat4& other) {
        data[0] += other[0]; data[1] += other[1]; data[2] += other[2]; data[3] += other[3];
        data[4] += other[4]; data[5] += other[5]; data[6] += other[6]; data[7] += other[7];
        data[8] += other[8]; data[9] += other[9]; data[10] += other[10]; data[11] += other[11];
        data[12] += other[12]; data[13] += other[13]; data[14] += other[14]; data[15] += other[15];
    }

    Mat4 Mat4::operator+ (const f32 val) const {
        return {
            data[0] + val, data[1] + val, data[2] + val, data[3] + val,
            data[4] + val, data[5] + val, data[6] + val, data[7] + val,
            data[8] + val, data[9] + val, data[10] + val, data[11] + val,
            data[12] + val, data[13] + val, data[14] + val, data[15] + val
        };
    }

    Mat4 Mat4::operator+ (const Mat4& other) const {
        return {
            data[0] + other[0], data[1] + other[1], data[2] + other[2], data[3] + other[3],
            data[4] + other[4], data[5] + other[5], data[6] + other[6], data[7] + other[7],
            data[8] + other[8], data[9] + other[9], data[10] + other[10], data[11] + other[11],
            data[12] + other[12], data[13] + other[13], data[14] + other[14], data[15] + other[15]
        };
    }

    void Mat4::operator-=(const f32 val) {
        data[0] -= val; data[1] -= val; data[2] -= val; data[3] -= val;
        data[4] -= val; data[5] -= val; data[6] -= val; data[7] -= val;
        data[8] -= val; data[9] -= val; data[10] -= val; data[11] -= val;
        data[12] -= val; data[13] -= val; data[14] -= val; data[15] -= val;
    }

    void Mat4::operator-=(const Mat4& other) {
        data[0] -= other[0]; data[1] -= other[1]; data[2] -= other[2]; data[3] -= other[3];
        data[4] -= other[4]; data[5] -= other[5]; data[6] -= other[6]; data[7] -= other[7];
        data[8] -= other[8]; data[9] -= other[9]; data[10] -= other[10]; data[11] -= other[11];
        data[12] -= other[12]; data[13] -= other[13]; data[14] -= other[14]; data[15] -= other[15];
    }

    Mat4 Mat4::operator- (const f32 val) const {
        return {
            data[0] - val, data[1] - val, data[2] - val, data[3] - val,
            data[4] - val, data[5] - val, data[6] - val, data[7] - val,
            data[8] - val, data[9] - val, data[10] - val, data[11] - val,
            data[12] - val, data[13] - val, data[14] - val, data[15] - val
        };
    }

    Mat4 Mat4::operator- (const Mat4& other) const {
        return {
            data[0] - other[0], data[1] - other[1], data[2] - other[2], data[3] - other[3],
            data[4] - other[4], data[5] - other[5], data[6] - other[6], data[7] - other[7],
            data[8] - other[8], data[9] - other[9], data[10] - other[10], data[11] - other[11],
            data[12] - other[12], data[13] - other[13], data[14] - other[14], data[15] - other[15]
        };
    }


    void Mat4::Rotate(Vec3 euler) {
        (*this) = Matrix4::Rotation(euler) * (*this);
    }

    void Mat4::Rotate(f32 x, f32 y, f32 z) {
        (*this) = Matrix4::Rotation(x, y, z) * (*this);
    }


    namespace Matrix4 {
        Mat4 Identity() {
            Mat4 m = {};
            m[0] = 1.0f;
            m[5] = 1.0f;
            m[10] = 1.0f;
            m[15] = 1.0f;
            return m;
        };

        Mat4 Translation(Vec3 displacement) {
            return Translation(displacement.x, displacement.y, displacement.z);
        }

        Mat4 Translation(f32 x, f32 y, f32 z) {
            Mat4 out = Identity();
            out[12] = x;
            out[13] = y;
            out[14] = z;
            return out;
        }

        Mat4 Rotation(Vec3 euler) {
            return Rotation(euler.x, euler.y, euler.z);
        }

        /*
            NOTE: Can definitely be optimised, look at more performant trig calcs.
        */

        Mat4 Rotation(f32 x, f32 y, f32 z) {
            Mat4 out = Identity();

            f32 sinX = sinf(DEG2RAD * x);
            f32 cosX = cosf(DEG2RAD * x);
            f32 sinY = sinf(DEG2RAD * y);
            f32 cosY = cosf(DEG2RAD * y);
            f32 sinZ = sinf(DEG2RAD * z);
            f32 cosZ = cosf(DEG2RAD * z);

            out[0]  = + (cosY * cosZ);
            out[1]  = - (cosY * sinZ);
            out[2]  = + (sinY);
            
            out[4]  = + (sinX * sinY * cosZ) + (cosX * sinZ);
            out[5]  = - (sinX * sinY * sinZ) + (cosX * cosZ); 
            out[6]  = - (sinX * cosY);

            out[8]  = - (cosX * sinY * cosZ) + (sinX * sinZ);
            out[9]  = + (cosX * sinY * sinZ) + (sinX * cosZ);
            out[10] = + (cosX * cosY);

            return out;
        }

        Mat4 Scale(Vec3 scale) {
            return Scale(scale.x, scale.y, scale.z);
        }

        Mat4 Scale(f32 x, f32 y, f32 z) {
            Mat4 out = Identity();
            out[0] = x;
            out[5] = y;
            out[10] = z;
            return out;
        }

        /*
            NOTE: For view matrices we need the transformation which brings the camera back 
            to the origin and then rotates it such that it points along the negative z-axis.
            i.e. translation of negative the camera pos, followed by rotation towards {0.0, 0.0, -1.0};
        */

        Mat4 ViewLookDir(Vec3 position, Vec3 forward, Vec3 up) {
            
            up.NormaliseInPlace();            
            forward = Vector3::Normalised(forward);
            Vec3 left = Vector3::Cross(up, forward);
            up = Vector3::Cross(forward, left);

            Mat4 out = Matrix4::Identity();

            out[0] = left.x;
            out[4] = left.y;
            out[8] = left.z;

            out[1] = up.x;
            out[5] = up.y;
            out[9] = up.z;

            out[2] = forward.x;
            out[6] = forward.y;
            out[10] = forward.z;

            out[12] = - Vector3::Dot(left, position);
            out[13] = - Vector3::Dot(up, position);
            out[14] = - Vector3::Dot(forward, position);

            return out;
        }

        Mat4 ViewLookAt(Vec3 position, Vec3 target, Vec3 up) {
            return ViewLookDir(position, position - target, up);
        }

        Mat4 Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
            f32 invWidth = 1.0f / (right - left);
            f32 invHeight = 1.0f / (top - bottom);
            f32 invDepth = 1.0f / (far - near);
            
            Mat4 out = Identity();
            out[0] = 2.0f * invWidth;
            out[5] = 2.0f * invHeight;
            out[10] = -2.0f * invDepth;
            out[12] = - (right + left) * invWidth;
            out[13] = - (top + bottom) * invHeight;
            out[14] = - (far + near) * invDepth;
            out[15] = 1.0f;
            return out;
        }

        Mat4 Perspective(f32 fovyInDeg, f32 aspect, f32 near, f32 far) {
            f32 invTan = 1.0f / tanf(DEG2RAD * fovyInDeg / 2.0f);
            f32 invZinterval = 1.0f / (far - near);

            Mat4 out = Identity();
            out[0] = (1.0f / aspect) * invTan;
            out[5] = invTan;
            out[10] = - (far + near) * invZinterval;
            out[14] = - 2.0f * far * near * invZinterval;
            out[11] = -1.0f;
            out[15] = 0.0f;
            return out;
        }
    };
};