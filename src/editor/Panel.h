#pragma once

#include <imgui.h>
#include <string>

#include "editor/model/Model.h"

namespace editor
{

    class Panel
    {
    private:
        std::string _name;

    public:
        const char *name() { return _name.c_str(); }

        void name(std::string name) { _name = name; }

        virtual ~Panel() {}

        void do_display(Model &model)
        {
            ImGui::PushID(this);
            ImGui::Begin(_name.c_str());

            display(model);

            ImGui::End();
            ImGui::PopID();
        }

        virtual void update(Model &, core::Time &) {}

        virtual void render(Model &) {}

        virtual void display(Model &) { ImGui::Text("Nothing to show here..."); }
    };
} // namespace editor
