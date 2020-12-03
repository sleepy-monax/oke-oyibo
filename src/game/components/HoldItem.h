#pragma once

#include "editor/Inspect.h"
#include "game/inventory/Stack.h"

namespace game
{
    struct HoldItem
    {
        int index = 0;
    };

} // namespace game
template <>
inline void inspect<game::HoldItem>(game::HoldItem &hold)
{
    ImGui::InputInt("Index", &hold.index);
}