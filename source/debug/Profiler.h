#pragma once

#include <chrono>
#include <imgui.h>

namespace debug
{
    class Profiler
    {
    private:
        static constexpr size_t RECORD_COUNT = 64;
        static uint64_t _current_frame;

        const char *_name = "Invalid";
        float _record[RECORD_COUNT] = {};
        uint64_t _last_frame;

    public:
        static void new_frame()
        {
            _current_frame++;
        }

        Profiler(const char *name) : _name(name)
        {
        }

        ~Profiler() {}

        template <typename TMeasuredFunction>
        void mesure(TMeasuredFunction function)
        {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float, std::micro> delta = end - start;

            if (_current_frame != _last_frame)
            {
                for (size_t i = 0; i < RECORD_COUNT - 1; i++)
                {
                    _record[i] = _record[i + 1];
                }

                _record[RECORD_COUNT - 1] = delta.count();

                _last_frame = _current_frame;
            }
            else
            {
                _record[RECORD_COUNT - 1] += delta.count();
            }
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
        }
    };
} // namespace debug