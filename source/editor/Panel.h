#pragma once

#include <imgui.h>
#include <string>

#include "core/game/UpdateContext.h"
#include "core/world/World.h"

namespace editor
{
    class Editor;

    class Panel
    {
    private:
        std::string _name;
        Editor &_editor;

    public:
        const char *name() { return _name.c_str(); }

        auto &editor() { return _editor; }

        Panel(Editor &editor, const char *name) : _name(name), _editor(editor)
        {
        }

        virtual ~Panel()
        {
        }

        void do_display()
        {
            ImGui::PushID(this);
            ImGui::Begin(_name.c_str());

            display();

            ImGui::End();
            ImGui::PopID();
        }

        virtual void update(core::game::UpdateContext &)
        {
        }

        virtual void render()
        {
        }

        virtual void display()
        {
            ImGui::Text("Nothing to show here!");
        }
    };
} // namespace editor
