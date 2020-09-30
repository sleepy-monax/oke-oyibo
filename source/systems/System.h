#pragma once

#include <string>

#include "debug/Profiler.h"
#include "loop/RenderContext.h"
#include "loop/UpdateContext.h"

namespace world
{
    class World;
} // namespace world

namespace systems
{
    class System
    {
    private:
        bool _enabled = true;
        bool _visible = true;

        std::string _name;

        debug::Profiler update_profiler{"Update"};
        debug::Profiler render_profiler{"Render"};
        debug::Profiler display_profiler{"Display"};

    public:
        System(const char *name) : _name(name + std::string(" System")) {}

        virtual ~System() {}

        void do_update(world::World &, loop::UpdateContext &);

        void do_render(world::World &, loop::RenderContext &);

        void do_display(world::World &);

        virtual void update(world::World &, loop::UpdateContext &) {}

        virtual void render(world::World &, loop::RenderContext &) {}

        virtual void display(world::World &) { ImGui::Text("Nothing to show here."); }
    };
} // namespace systems
