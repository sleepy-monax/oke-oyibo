#pragma once

#include <raylib.h>

namespace game
{
    struct Thirst
    {
        float max_thirst;
        float current_thirst;
    };

} // namespace game

template <>
inline void inspect<game::Thirst>(game::Thirst &thirst)
{
    ImGui::InputFloat("currentThirst##Thirst", &thirst.current_thirst);
    ImGui::InputFloat("maxThirst##Thirst", &thirst.max_thirst);
}
