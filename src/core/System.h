#pragma once

#include <string>

#include "core/Camera.h"
#include "core/Probe.h"
#include "core/Time.h"
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

        Probe _update_probe{"Update"};
        Probe _render_probe{"Render"};

    public:
        const char *name() { return _name.c_str(); }

        bool enable() { return _enable; }

        void enable(bool enable) { _enable = enable; }

        bool visible() { return _visible; }

        void visible(bool visible) { _visible = visible; }

        Probe &update_probe() { return _update_probe; }

        Probe &render_probe() { return _render_probe; }

        System(const char *name) :
            _name(name + std::string(" System")) {}

        virtual ~System() {}

        void do_update(World &, Time &);

        void do_render(World &, Camera &);

        virtual void update(World &, Time &) {}

        virtual void render(World &, Camera &) {}
    };
} // namespace core

template <class TSystem>
void inspect_system(core::World &world, TSystem &system)
{
    __unused(world);
    inspect(system);
}
