#pragma once

#include "utils/Vector.h"

#include "game/inventory/Stack.h"

namespace game
{
    struct Craft
    {
        Stack result;
        utils::Vector<Stack> ingredients;
    };
} // namespace game
