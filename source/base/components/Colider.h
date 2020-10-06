#pragma once

#include "editor/Inspect.h"

namespace base
{
    struct Colider
    {
        float offx;
        float offy;
        float w;
        float h;
    };
} // namespace base

template <>
inline void inspect<base::Colider>(base::Colider &col)
{
    ImGui::InputFloat("offx##Colider", &col.offx);
    ImGui::InputFloat("offy##Colider", &col.offy);
    ImGui::InputFloat("w##Colider", &col.w);
    ImGui::InputFloat("h##Colider", &col.h);
}