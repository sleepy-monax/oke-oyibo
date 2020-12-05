#pragma once

#include <raylib.h>

namespace game
{
    struct Stamina
    {
        float maximum;
        float current;
    };
} // namespace game

template <>
inline void inspect<game::Stamina>(game::Stamina &stamina)
{
    ImGui::InputFloat("current##Stamina", &stamina.current);
    ImGui::InputFloat("maximum##Stamina", &stamina.maximum);
}
