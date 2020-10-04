#pragma once

#include "editor/Editor.h"

namespace editor
{
    class EntityList : public Panel
    {
    private:
        std::set<ENTT_ID_TYPE> _filters{};

    public:
        EntityList(Editor &editor) : Panel(editor, "Entities") {}

        void display_entity(entt::entity e);

        void display() override;
    };
} // namespace editor
