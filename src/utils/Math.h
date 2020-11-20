#pragma once

namespace utils
{
    template <typename TScalar>
    static inline TScalar lerp(TScalar from, TScalar to, double t)
    {
        return from + t * (to - from);
    }
} // namespace utils
