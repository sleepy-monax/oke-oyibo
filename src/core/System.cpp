#include "core/System.h"

namespace core
{
    void System::do_update(World &world, Time &context)
    {
        _update_probe.mesure_time([&]() {
            if (_enable)
            {
                update(world, context);
            }
        });
    }

    void System::do_render(World &world, Camera &context)
    {
        _render_probe.mesure_time([&]() {
            if (_visible)
            {
                render(world, context);
            }
        });
    }
} // namespace core
