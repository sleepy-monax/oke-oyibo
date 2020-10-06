#pragma once

#include <imgui.h>
#include <raylib.h>

#include "core/glue/ImGuiExtension.h"
#include "editor/Inspect.h"

namespace base
{
    struct LightSource
    {
        float radius;
        Color color = WHITE;
    };
} // namespace base

template <>
inline void inspect<base::LightSource>(base::LightSource &light)
{
    ImGui::InputFloat("radius##LightSource", &light.radius);
    ImGui::SliderUint8("red##LightSource", &light.color.r, 0, 255);
    ImGui::SliderUint8("green##LightSource", &light.color.g, 0, 255);
    ImGui::SliderUint8("blue##LightSource", &light.color.b, 0, 255);
    ImGui::SliderUint8("alpha##LightSource", &light.color.a, 0, 255);
}