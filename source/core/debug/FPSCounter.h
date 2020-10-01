#pragma once

#include <imgui.h>
#include <raylib.h>

namespace core::debug
{
    class FPSCounter
    {
    private:
        static constexpr size_t RECORD_COUNT = 60 * 10;
        float _record[RECORD_COUNT] = {};

    public:
        FPSCounter() {}

        void mesure_and_display()
        {
            for (size_t i = 0; i < RECORD_COUNT - 1; i++)
            {
                _record[i] = _record[i + 1];
            }

            _record[RECORD_COUNT - 1] = GetFPS();

            float average = 0;

            for (size_t i = 0; i < IM_ARRAYSIZE(_record); i++)
            {
                average += _record[i];
            }

            average /= IM_ARRAYSIZE(_record);

            ImGui::Text("avg: %3.0ffps", average);
            ImGui::PlotLines("FPS", _record, IM_ARRAYSIZE(_record), 0, nullptr, 0, 100, ImVec2(0, 24));
        }
    };
} // namespace core::debug
