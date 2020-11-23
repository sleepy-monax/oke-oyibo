#pragma once

#include <imgui.h>
#include <raylib.h>

#include "core/Probe.h"

namespace editor
{
    class FPSCounter: public core::Probe
    {
    public:
        FPSCounter() :
            Probe("FPSCounter") {}
        void mesure() { Probe::mesure(GetFPS()); }
    };
} // namespace editor

template <>
inline void inspect<editor::FPSCounter>(editor::FPSCounter &fps_counter)
{
    ImGui::Text("%s", fps_counter.name());
    ImGui::Text("avg: %3.0ffps", fps_counter.average());
    ImGui::PlotLines("FPS", fps_counter.record(), fps_counter.size(), 0, nullptr, 0, 100, ImVec2(0, 24));
}
