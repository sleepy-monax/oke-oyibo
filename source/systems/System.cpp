#include "systems/System.h"

namespace systems
{
    void System::do_update(world::World &world)
    {
        update_profiler.mesure([&]() {
            update(world);
        });
    }

    void System::do_render(world::World &world)
    {
        render_profiler.mesure([&]() {
            render(world);
        });
    }

    void System::do_display(world::World &world)
    {
        ImGui::Begin("Systems");
        display_profiler.mesure([&]() {
            if (ImGui::CollapsingHeader(_name.c_str()))
            {
                display(world);
            }
        });
        ImGui::End();

        ImGui::Begin("Profiler");
        if (ImGui::CollapsingHeader(_name.c_str()))
        {
            update_profiler.display();
            render_profiler.display();
            display_profiler.display();
        }
        ImGui::End();
    }

} // namespace systems
