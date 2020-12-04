#pragma once

#include <core/Texture.h>
#include <string>

namespace core
{
    struct Tile
    {
        static constexpr auto SIZE = 16;

        Texture texture;
        int flags;
    };
} // namespace core
