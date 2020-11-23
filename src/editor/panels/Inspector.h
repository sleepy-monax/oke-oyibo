#pragma once

#include "editor/Panel.h"

namespace editor
{
    class Inspector : public Panel
    {
    private:
    public:
        Inspector()
        {
            name("Inspector");
        }

        bool entity_has_component(Model &model, ENTT_ID_TYPE component)
        {
            ENTT_ID_TYPE type[] = {component};
            return model.entities().runtime_view(std::cbegin(type), std::cend(type)).contains(model.selected_entity);
        }

        void display(Model &model)
        {
            ImGui::Text("Editing entity: %d", entt::to_integral(model.selected_entity));

            model.registry().foreach_components([&](auto &id, auto &info) {
                if (entity_has_component(model, id))
                {
                    if (ImGui::CollapsingHeader(info.name.c_str()))
                    {
                        ImGui::Indent();
                        ImGui::PushID("Widget");
                        info.inspect(model.world, model.selected_entity);
                        ImGui::PopID();
                        ImGui::Unindent();
                    }
                }

                return utils::Iteration::CONTINUE;
            });
        }
    };
} // namespace editor
