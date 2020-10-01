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
                ImGui::Indent();

                ImGui::Text("State:");
                ImGui::Checkbox("Enable", &_enabled);
                ImGui::SameLine();
                ImGui::Checkbox("Visible", &_visible);

                ImGui::Separator();
                ImGui::Text("Properities:");

                display(world);

                ImGui::Unindent();
            }
            ImGui::PopID();
        });
        ImGui::End();

        ImGui::Begin("Profiler");
        if (ImGui::CollapsingHeader(_name.c_str()))
        {
            ImGui::Indent();

            update_profiler.display();
            render_profiler.display();
            display_profiler.display();

            ImGui::Unindent();
        }
        ImGui::End();
    }

} // namespace systems
