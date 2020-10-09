#pragma once

#include "editor/Editor.h"

namespace editor
{
    class EntityEditor : public Panel
    {
    private:
        entt::entity _entity;

    public:
        void entity(entt::entity e) { _entity = e; }

        EntityEditor(Editor &editor, entt::entity entity)
            : Panel(editor, "Entity"), _entity(entity)
        {
        }

        bool entity_has_component(ENTT_ID_TYPE component);

        void display() override;
    };
} // namespace editor
