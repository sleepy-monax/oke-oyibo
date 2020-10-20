#pragma once

namespace utils
{
    template <typename TScalar>
    TScalar lerp(TScalar from, TScalar to, double t)
    {
        return from + t * (to - from);
    }
} // namespace utils
