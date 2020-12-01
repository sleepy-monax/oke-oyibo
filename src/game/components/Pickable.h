#pragma once

#include "game/inventory/Stack.h"
#include "editor/Inspect.h"

namespace game
{
    struct Pickable
    {
        game::Stack stack;
    };
} // namespace game
template <>
inline void inspect<game::Pickable>(game::Pickable &pick)
{
    inspect(pick.stack);
}