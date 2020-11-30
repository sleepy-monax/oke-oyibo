#pragma once

#include <raylib.h>

namespace game
{
    struct Stamina {
        float max_stamina;
        float current_stamina;
    };

} // namespace game

template <>
inline void inspect<game::Stamina>(game::Stamina &stamina)
{
    ImGui::InputFloat("currentStamina##Stamina", &stamina.current_stamina);
    ImGui::InputFloat("maxStamina##Stamina", &stamina.max_stamina);
}
