#include "maths/random.hpp"

namespace Noether {
    namespace Random {
        static u32 s_GlobalSeed;

        f32 F32() {
            return F32(s_GlobalSeed);
        }

        f32 F32(f32 min, f32 max) {
            return F32(s_GlobalSeed, min, max);
        }

        u32 U32() {
            return U32(s_GlobalSeed);
        }

        u32 U32(u32 min, u32 max) {
            return U32(s_GlobalSeed, min, max);
        }

        Noether::Vec2 Vec2() {
            return Vec2(s_GlobalSeed);
        }

        Noether::Vec3 Vec3() {
            return Vec3(s_GlobalSeed);
        }
    }
};