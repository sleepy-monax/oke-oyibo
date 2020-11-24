#pragma once

#include "editor/Panel.h"

namespace editor
{
    class Systems: public Panel
    {
    private:
    public:
        Systems()
        {
            name("Systems");
        }

        void display(Model &model) override
        {
            model.systems().foreach ([&](auto &id, auto &system) {
                auto &info = model.registry().system_info(id);

                if (ImGui::CollapsingHeader(info.name.c_str()))
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

                    info.inspect(*model.world, *system);

                    ImGui::Unindent();
                    ImGui::PopID();
                }

                return utils::Iteration::CONTINUE;
            });
        }
    };
} // namespace editor
