#pragma once

#include "editor/Inspect.h"

namespace core::components
{
    struct Colider
    {
        float offx;
        float offy;
        float w;
        float h;
    };
} // namespace core::components

template <>
void inspect<core::components::Colider>(core::components::Colider &col)
{
    ImGui::InputFloat("offx##Colider", &col.offx);
    ImGui::InputFloat("offy##Colider", &col.offy);
    ImGui::InputFloat("w##Colider", &col.w);
    ImGui::InputFloat("h##Colider", &col.h);
}