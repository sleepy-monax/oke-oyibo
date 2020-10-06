#pragma once

#include <imgui.h>
#include <raylib.h>

#include "core/debug/Probe.h"

namespace core::debug
{
    class FPSCounter : public Probe
    {
    public:
        FPSCounter() : Probe("FPSCounter") {}
        void mesure_fps() { mesure(GetFPS()); }
    };
} // namespace core::debug

template <>
inline void inspect<core::debug::FPSCounter>(core::debug::FPSCounter &fps_counter)
{
    ImGui::Text("%s", fps_counter.name());
    ImGui::Text("avg: %3.0ffps", fps_counter.average());
    ImGui::PlotLines("FPS", fps_counter.record(), fps_counter.size(), 0, nullptr, 0, 100, ImVec2(0, 24));
}
