#pragma once

#include <chrono>
#include <imgui.h>

namespace debug
{
    class Profiler
    {
    private:
        static constexpr size_t RECORD_COUNT = 64;

        const char *_name = "Invalid";
        float _record[RECORD_COUNT] = {};

    public:
        Profiler(const char *name) : _name(name) {}

        ~Profiler() {}

        template <typename TMeasuredFunction>
        void mesure(TMeasuredFunction function)
        {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float, std::micro> delta = end - start;

            for (size_t i = 0; i < RECORD_COUNT - 1; i++)
            {
                _record[i] = _record[i + 1];
            }

            _record[RECORD_COUNT - 1] = delta.count();
        }

        void display()
        {
            float average = 0;

            for (size_t i = 0; i < IM_ARRAYSIZE(_record); i++)
            {
                average += _record[i];
            }

            average /= IM_ARRAYSIZE(_record);

            ImGui::Text("%s", _name);
            ImGui::Text("avg: %5.2fµs budget: %3.2f%%", average, average / 160.0);
            ImGui::PlotLines("(µs)", _record, IM_ARRAYSIZE(_record), 0, nullptr, 0, 16 * 100, ImVec2(0, 24));
            ImGui::Separator();
        }
    };
} // namespace debug