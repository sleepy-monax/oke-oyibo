#pragma once

#include <imgui.h>
#include <raylib.h>

#include "editor/Inspect.h"

namespace core::components
{
    struct LightSource
    {
        float radius;
        Color color;
    };
} // namespace core::components

template <>
inline void inspect<core::components::LightSource>(core::components::LightSource &light)
{
    ImGui::InputFloat("offx##LightSource", &light.radius);
    ImGui::SliderInt("red##LightSource", (int *)&light.color.r, 0, 255);
    ImGui::SliderInt("green##LightSource", (int *)&light.color.r, 0, 255);
    ImGui::SliderInt("blue##LightSource", (int *)&light.color.r, 0, 255);
}