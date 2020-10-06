#pragma once

#include <string>

#include "core/RenderContext.h"
#include "core/UpdateContext.h"
#include "core/debug/Probe.h"
#include "editor/Inspect.h"

namespace core
{
    class World;
} // namespace core

namespace core
{
    class System
    {
    private:
        std::string _name;

        bool _enable = true;
        bool _visible = true;

        debug::Probe _update_probe{"Update"};
        debug::Probe _render_probe{"Render"};

    public:
        const char *name() { return _name.c_str(); }

        bool enable() { return _enable; }

        void enable(bool enable) { _enable = enable; }

        bool visible() { return _visible; }

        void visible(bool visible) { _visible = visible; }

        debug::Probe &update_probe() { return _update_probe; }

        debug::Probe &render_probe() { return _render_probe; }

        System(const char *name) : _name(name + std::string(" System")) {}

        virtual ~System() {}

        void do_update(World &, UpdateContext &);

        void do_render(World &, RenderContext &);

        virtual void update(World &, UpdateContext &) {}

        virtual void render(World &, RenderContext &) {}
    };
} // namespace core

template <class TSystem>
void inspect_system(core::World &world, TSystem &system)
{
    __unused(world);
    inspect(system);
}
