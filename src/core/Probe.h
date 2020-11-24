#pragma once

#include <chrono>
#include <concepts>

#include "core/glue/Glue.h"
#include "editor/Inspect.h"

namespace core
{
    class Probe
    {
    private:
        static constexpr size_t RECORD_COUNT = 64;

        const char *_name = "Invalid";
        float _record[RECORD_COUNT] = {};
        uint64_t _last_frame;

    public:
        const char *name() const { return _name; }

        const float *record() const { return _record; }

        size_t size() const { return RECORD_COUNT; }

        float average() const
        {
            float total = 0;

            for (size_t i = 0; i < RECORD_COUNT; i++)
            {
                total += _record[i];
            }

            return total / RECORD_COUNT;
        }

        Probe(const char *name) :
            _name(name)
        {
        }

        void mesure(std::invocable auto function)
        {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float, std::micro> delta = end - start;

            mesure(delta.count());
        }

        void mesure(float value)
        {
            if (glue::current_frame() != _last_frame)
            {
                for (size_t i = 0; i < RECORD_COUNT - 1; i++)
                {
                    _record[i] = _record[i + 1];
                }

                _record[RECORD_COUNT - 1] = value;

                _last_frame = glue::current_frame();
            }
            else
            {
                _record[RECORD_COUNT - 1] += value;
            }
        }
    };
} // namespace core

template <>
inline void inspect<core::Probe>(core::Probe &probe)
{
    ImGui::Text("%s", probe.name());
    ImGui::Text("avg: %5.2fµs budget: %3.2f%%", probe.average(), probe.average() / 160.0);
    ImGui::PlotLines("(µs)", probe.record(), probe.size(), 0, nullptr, 0, 16 * 100, ImVec2(0, 24));
}
