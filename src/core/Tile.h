#pragma once

#include <core/Texture.h>
#include <string>

namespace core
{
    struct Tile
    {
        static constexpr auto SIZE = 16;

        static constexpr auto LIQUID = 1 << 0;
        static constexpr auto SOLID = 1 << 1;

        Texture texture;
        int flags;
    };
} // namespace core
