#pragma once

#include <string>

#include "debug/Profiler.h"
#include "game/RenderContext.h"
#include "game/UpdateContext.h"

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
        bool _detached = false;

        std::string _name;

        debug::Profiler _update_profiler{"Update"};
        debug::Profiler _render_profiler{"Render"};
        debug::Profiler _display_profiler{"Display"};

        void display_state();
        void display_profiler();
        void display_properties(world::World &);

    public:
        System(const char *name) : _name(name + std::string(" System")) {}

        virtual ~System() {}

        void do_update(world::World &, game::UpdateContext &);

        void do_render(world::World &, game::RenderContext &);

        void do_display(world::World &);

        virtual void update(world::World &, game::UpdateContext &) {}

        virtual void render(world::World &, game::RenderContext &) {}

        virtual void display(world::World &) { ImGui::Text("Nothing to show here."); }
    };
} // namespace systems
