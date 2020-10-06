#pragma once

#include "editor/Editor.h"

namespace editor
{
    class SystemList : public Panel
    {
    private:
    public:
        SystemList(Editor &editor) : Panel(editor, "Systems") {}

        void display() override;
    };
} // namespace editor