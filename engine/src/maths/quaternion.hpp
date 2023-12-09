#pragma once

#include "core/defines.hpp"

namespace Noether {
    struct Quat {
        f32 r;
        f32 i;
        f32 j;
        f32 k;

        inline void NormaliseInPlace() {
            f32 norm = r*r + i*i + j*j + k*k;

            if (norm == 0.0f) {
                r = 1.0f;
                return;
            }

            f32 inv = 1.0f / sqrtf(norm);
            r *= inv;
            i *= inv;
            j *= inv;
            k *= inv;
        }
    };


    namespace Quaternion {
        inline Quat Identity() { return {1.0f, 0.0f, 0.0f, 0.0f}; }

        Quat Normalised(const Quat& q);
    };
};