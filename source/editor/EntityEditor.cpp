#include "editor/EntityEditor.h"
#include "core/Registry.h"

namespace editor
{
    bool EntityEditor::entity_has_component(ENTT_ID_TYPE component)
    {
        ENTT_ID_TYPE type[] = {component};
        return editor().entities().runtime_view(std::cbegin(type), std::cend(type)).contains(_entity);
    }

    void EntityEditor::display()
    {
        ImGui::Text("Editing entity: %d", entt::to_integral(_entity));

        editor().registry().foreach_components([this](auto &id, auto &info) {
            if (entity_has_component(id))
            {
                if (ImGui::CollapsingHeader(info.name.c_str()))
                {
                    ImGui::Indent();
                    ImGui::PushID("Widget");
                    info.inspect(editor().world(), _entity);
                    ImGui::PopID();
                    ImGui::Unindent();
                }
            }
        });
    }
} // namespace editor
