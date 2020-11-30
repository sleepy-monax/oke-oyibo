#pragma once

#include "utils/Vec.h"

namespace utils
{
    template <typename TScalar>
    static inline TScalar lerp(TScalar from, TScalar to, double t)
    {
        return from + t * (to - from);
    }

    template <typename TScalar>
    static inline Vec2<TScalar> lerp(Vec2<TScalar> from, Vec2<TScalar> to, double t)
    {
        return {
            lerp(from.x(), to.x(), t),
            lerp(from.y(), to.y(), t),
        };
    }
} // namespace utils
