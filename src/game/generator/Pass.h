#pragma once

#include "core/World.h"

namespace game
{
    struct Pass
    {
        virtual ~Pass() {}
        virtual void apply(core::World &){};
    };
} // namespace game
