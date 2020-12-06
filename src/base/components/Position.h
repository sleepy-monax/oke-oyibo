#pragma once

#include "editor/Inspect.h"
#include "utils/Vec.h"

namespace base
{
    struct Position
    {
        float x;
        float y;
        float z;

        utils::Vec2f pos2d()
        {
            return {x, y};
        }

        utils::Vec2f operator()()
        {
            return {x, y};
        }
    };

} // namespace base

template <>
inline void inspect<base::Position>(base::Position &pos)
{
    ImGui::InputFloat("x##Position", &pos.x);
    ImGui::InputFloat("y##Position", &pos.y);
    ImGui::InputFloat("z##Position", &pos.z);
}
