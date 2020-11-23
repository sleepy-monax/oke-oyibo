#pragma once

#include <raylib.h>

namespace game
{
    struct Hunger
    {
        float max_food;
        float current_food;
    };

} // namespace game

template <>
inline void inspect<game::Hunger>(game::Hunger &hunger)
{
    ImGui::InputFloat("currentFood##Hunger", &hunger.current_food);
    ImGui::InputFloat("maxFood##Hunger", &hunger.max_food);
}


