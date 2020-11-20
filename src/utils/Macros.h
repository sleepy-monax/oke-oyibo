#pragma once

#include <utility>

#define __packed __attribute__((packed))

template <typename TFrom, typename TTo>
constexpr TTo &sketchy_cast(TFrom &from)
{
    return *reinterpret_cast<TTo *>(&from);
}

#define __unused(__stuff) (void)(__stuff)

#define __clamp(__v, __lower, __upper) (MAX(MIN((__v), (__upper)), (__lower)))

#define MIN(__x, __y) ((__x) < (__y) ? (__x) : (__y))

#define MAX(__x, __y) ((__x) > (__y) ? (__x) : (__y))

#define __noncopyable(__class_name)              \
    __class_name(const __class_name &) = delete; \
    __class_name &operator=(const __class_name &) = delete;

#define __nonmovable(__class_name)                \
    __class_name(const __class_name &&) = delete; \
    __class_name &operator=(const __class_name &&) = delete;
