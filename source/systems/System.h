#pragma once

#include <string>

#include "debug/Profiler.h"

namespace world
{
    class World;
} // namespace world

namespace systems
{
    class System
    {
    private:
        std::string _name;

        debug::Profiler update_profiler{"Update"};
        debug::Profiler render_profiler{"Render"};
        debug::Profiler display_profiler{"Display"};

    public:
        System(const char *name) : _name(name + std::string(" system")) {}

        virtual ~System() {}

        void do_update(world::World &);

        void do_render(world::World &);

        void do_display(world::World &);

        virtual void update(world::World &) {}

        virtual void render(world::World &) {}

        virtual void display(world::World &) { ImGui::Text("Nothing to show here."); }
    };
} // namespace systems
