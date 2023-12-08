#include "maths/quaternion.hpp"

namespace Noether {
    namespace Quaternion {
        Quat Normalised(const Quat& q) {
            f32 norm = q.r*q.r + q.i*q.i + q.j*q.j + q.k*q.k;

            if (norm == 0.0f) {
                return Quaternion::Identity();
            }

            f32 inv = 1.0f / sqrtf(norm);
            return { q.r * inv, q.i * inv, q.j * inv, q.k * inv };
        }
    };
};