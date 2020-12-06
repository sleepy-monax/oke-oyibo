#pragma once

#include "utils/Vector.h"

#include "game/menu/MenuLevel.h"

namespace game
{
    struct Menu
    {
        utils::Vector<MenuLevel> levels;
        size_t selected_option;
    };

} // namespace game
