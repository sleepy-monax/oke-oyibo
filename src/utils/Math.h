#pragma once

namespace utils
{
    template <typename T>
    T lerp(T from, T to, double t)
    {
        return from + t * (to - from);
    }
} // namespace utils
