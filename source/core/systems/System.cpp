#include "core/systems/System.h"
#include "core/glue/ImGuiExtension.h"

namespace core::systems
{
    void System::do_update(world::World &world, game::UpdateContext &context)
    {
        _update_profiler.mesure([&]() {
            if (_enabled)
            {
                update(world, context);
            }
        });
    }

    void System::do_render(world::World &world, game::RenderContext &context)
    {
        _render_profiler.mesure([&]() {
            if (_visible)
            {
                render(world, context);
            }
        });
    }

    void System::display_state()
    {
        ImGui::Text("State:");

        ImGui::Checkbox("Enable", &_enabled);
        ImGui::SameLine();
        ImGui::Help("Disable this system by preventing update() run.");

        ImGui::SameLine();

        ImGui::Checkbox("Visible", &_visible);
        ImGui::SameLine();
        ImGui::Help("Hide this system by preventing render() run.");

        ImGui::SameLine();

        ImGui::Checkbox("Detache", &_detached);
        ImGui::SameLine();
        ImGui::Help("Detache this system properties in a different window.");
    }

    void System::display_properties(world::World &world)
    {
        ImGui::Text("Properties:");
        display(world);
    }

    void System::display_profiler()
    {
        ImGui::Text("Profile:");

        if (_enabled)
        {
            _update_profiler.display();
        }
        else
        {
            ImGui::Text("(Disabled)");
        }

        ImGui::Separator();

        if (_visible)
        {
            _render_profiler.display();
        }
        else
        {
            ImGui::Text("(Hidden)");
        }

        ImGui::Separator();

        _display_profiler.display();
    }

    void System::do_display(world::World &world)
    {
        ImGui::Begin("Systems");

        _display_profiler.mesure([&]() {
            ImGui::PushID(this);
            if (ImGui::CollapsingHeader(_name.c_str()))
            {
                ImGui::Indent();

                display_state();

                if (_detached)
                {
                    ImGui::Text("(This system's properties are in a different window.)");
                    ImGui::Begin(_name.c_str());
                }
                else
                {
                    ImGui::Separator();
                    ImGui::Separator();
                }

                display_properties(world);

                ImGui::Separator();
                ImGui::Separator();

                display_profiler();

                if (_detached)
                {
                    ImGui::End();
                }

                ImGui::Unindent();
            }
            ImGui::PopID();
        });
        ImGui::End();
    }

} // namespace core::systems
