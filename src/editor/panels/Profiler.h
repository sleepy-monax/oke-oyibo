#pragma once

#include "editor/Panel.h"

namespace editor
{
    class Profiler: public Panel
    {
    private:
    public:
        Profiler()
        {
            name("Profiler");
        }

        void display(Model &model) override
        {
            inspect(model.fps);
            inspect(model.update_time);
            inspect(model.render_time);
            inspect(model.display_time);
        }
    };
} // namespace editor
