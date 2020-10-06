#include <imgui.h>

#include "core/Registry.h"
#include "editor/SystemList.h"

namespace editor
{
    void SystemList::display()
    {
        editor().system().foreach ([&](auto &id, auto &system) {
            if (ImGui::CollapsingHeader(system->name()))
            {
                ImGui::PushID(system.naked());
                ImGui::Indent();

                bool enable = system->enable();
                ImGui::Checkbox("Enabled", &enable);
                system->enable(enable);

                ImGui::SameLine();

                bool visible = system->visible();
                ImGui::Checkbox("Visible", &visible);
                system->visible(visible);

                ImGui::Separator();
                ImGui::Separator();
                ImGui::Text("Probes:");

                inspect(system->update_probe());
                inspect(system->render_probe());

                ImGui::Separator();
                ImGui::Separator();
                ImGui::Text("Properties:");

                editor().registry().system_info(id).inspect(editor().world(), *system);

                ImGui::Unindent();
                ImGui::PopID();
            }

            return utils::Iteration::CONTINUE;
        });
    }
} // namespace editor
