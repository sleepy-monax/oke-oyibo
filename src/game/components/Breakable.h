#pragma once

#include "editor/Inspect.h"
#include "game/inventory/Stack.h"

namespace game
{
    struct Breakable
    {
        game::Stack stack;
        int durability;
    };

} // namespace game
template <>
inline void inspect<game::Breakable>(game::Breakable &breakable)
{
    inspect(breakable.stack);
    ImGui::InputInt("Durability", &breakable.durability);
}