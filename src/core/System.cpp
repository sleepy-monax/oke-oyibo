#include "core/System.h"

namespace core
{
    void System::do_update(World &world, Time &time)
    {
        _update_probe.mesure([&]() {
            if (_enable)
            {
                update(world, time);
            }
        });
    }

    void System::do_render(World &world, Camera &camera)
    {
        _render_probe.mesure([&]() {
            if (_visible)
            {
                render(world, camera);
            }
        });
    }
} // namespace core
