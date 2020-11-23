#pragma once

#include "editor/Editor.h"

namespace editor
{
    class Entities : public Panel
    {
    private:
        std::set<ENTT_ID_TYPE> _filters{};

    public:
        Entities() : Panel()
        {
            name("Entities");
        }

        void display_entity(Model &model, entt::entity e)
        {
            if (model.entities().valid(e))
            {
                ImGui::Text("Id: %d", entt::to_integral(e));

                ImGui::SameLine();

                if (ImGui::Button("edit"))
                {
                    model.selected_entity = e;
                }
            }
            else
            {
                ImGui::Text("Invalid Entity: %d", entt::to_integral(e));
            }
        }

        void display(Model &model) override
        {
            if (ImGui::CollapsingHeader("Filters"))
            {
                ImGui::Indent();

                if (ImGui::Button("Clear All"))
                {
                    _filters.clear();
                }

                model.registry().foreach_components([&](auto &id, auto &info) {
                    bool present = _filters.count(id);
                    bool active = present;

                    ImGui::Checkbox(info.name.c_str(), &active);

                    if (present && !active)
                    {
                        _filters.erase(id);
                    }
                    else if (!present && active)
                    {
                        _filters.emplace(id);
                    }

                    return utils::Iteration::CONTINUE;
                });

                ImGui::Unindent();
            }

            ImGui::Separator();
            ImGui::BeginChild("Matching Entities");

            if (_filters.empty())
            {
                model.entities().orphans([&](auto e) {
                    display_entity(model, e);
                });
            }
            else
            {
                auto view = model.entities().runtime_view(_filters.begin(), _filters.end());

                for (auto e : view)
                {
                    display_entity(model, e);
                }
            }

            ImGui::EndChild();
        }
    };
} // namespace editor
