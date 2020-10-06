#pragma once

#include <imgui.h>
#include <raylib.h>

#include "core/glue/ImGuiExtension.h"
#include "editor/Inspect.h"

namespace core::components
{
    struct LightSource
    {
        float radius;
        Color color = WHITE;
    };
} // namespace core::components

template <>
inline void inspect<core::components::LightSource>(core::components::LightSource &light)
{
    ImGui::InputFloat("radius##LightSource", &light.radius);
    ImGui::SliderUint8("red##LightSource", &light.color.r, 0, 255);
    ImGui::SliderUint8("green##LightSource", &light.color.g, 0, 255);
    ImGui::SliderUint8("blue##LightSource", &light.color.b, 0, 255);
    ImGui::SliderUint8("alpha##LightSource", &light.color.a, 0, 255);
}