#pragma once

#include "core/Texture.h"

#include "editor/Inspect.h"

namespace base
{
    struct Sprite
    {
        core::Texture texture;
        float flash = 0;
    };
} // namespace base
