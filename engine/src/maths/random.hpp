#pragma once

#include "core/hash.hpp"

#include "maths/maths.hpp"
#include "maths/vector.hpp"

namespace Noether {
    namespace Random {
        f32 F32();
        f32 F32(f32 min, f32 max);
        u32 U32();
        u32 U32(u32 min, u32 max);
        u64 U64();
        u64 U64(u32 min, u32 max);
        Noether::Vec2 Vec2();
        Noether::Vec3 Vec3();

        inline f32 F32(u32& seed) {
            seed = hash_pcg(seed);
            return (f32)seed / (f32)UINT32_MAX;
        }

        inline f32 F32(u32& seed, f32 min, f32 max) {
            return Maths::Lerp(min, max, F32(seed));
        }

        inline u32 U32(u32& seed) {
            seed = hash_pcg(seed);
            return seed;
        }

        inline u32 U32(u32& seed, u32 min, u32 max) {
            return min + (U32(seed) % (max - min + 1));
        }

        inline u64 U64(u32& seed) {
            u32 bottom = hash_pcg(seed);
            u32 top = hash_pcg(bottom);
            seed = top;
            return (top << 32) & bottom;
        }

        inline u64 U64(u32& seed, u64 min, u64 max) {
            return min + (U64(seed) % (max - min + 1));
        }

        inline Noether::Vec2 Vec2(u32& seed) {
            return { F32(seed), F32(seed) };
        }

        inline Noether::Vec3 Vec3(u32& seed) {
            return { F32(seed), F32(seed), F32(seed) };
        }
    };
};