#include "systems/System.h"

namespace systems
{
    void System::do_update(world::World &world, loop::UpdateContext &context)
    {
        update_profiler.mesure([&]() {
            if (_enabled)
            {
                update(world, context);
            }
        });
    }

    void System::do_render(world::World &world, loop::RenderContext &context)
    {
        render_profiler.mesure([&]() {
            if (_visible)
            {
                render(world, context);
            }
        });
    }

    void System::do_display(world::World &world)
    {
        ImGui::Begin("Systems");

        display_profiler.mesure([&]() {
            ImGui::PushID(this);
            if (ImGui::CollapsingHeader(_name.c_str()))
            {
                ImGui::Checkbox("Enable", &_enabled);
                ImGui::Checkbox("Visible", &_visible);
                display(world);
            }
            ImGui::PopID();
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
