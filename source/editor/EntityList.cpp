#include "editor/EntityList.h"
#include "core/Registry.h"
#include "editor/EntityEditor.h"

namespace editor
{
    void EntityList::display_entity(entt::entity e)
    {
        if (editor().entities().valid(e))
        {
            ImGui::Text("Id: %d", entt::to_integral(e));

            ImGui::SameLine();

            if (ImGui::Button("edit"))
            {
                editor().open<EntityEditor>(e);
            }
        }
        else
        {
            ImGui::Text("Invalid Entity: %d", entt::to_integral(e));
        }
    }

    void EntityList::display()
    {
        if (ImGui::CollapsingHeader("Filters"))
        {
            ImGui::Indent();

            if (ImGui::Button("Clear All"))
            {
                _filters.clear();
            }

            editor().registry().foreach_components([this](auto &id, auto &info) {
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
            });

            ImGui::Unindent();
        }

        ImGui::Separator();
        ImGui::BeginChild("Matching Entities");

        if (_filters.empty())
        {
            editor().entities().orphans([this](auto e) {
                display_entity(e);
            });
        }
        else
        {
            auto view = editor().entities().runtime_view(_filters.begin(), _filters.end());

            for (auto e : view)
            {
                display_entity(e);
            }
        }

        ImGui::EndChild();
    }

} // namespace editor