#include "core/systems/System.h"

namespace core::systems
{
    void System::do_update(world::World &world, game::UpdateContext &context)
    {
        _update_probe.mesure_time([&]() {
            if (_enable)
            {
                update(world, context);
            }
        });
    }

    void System::do_render(world::World &world, game::RenderContext &context)
    {
        _render_probe.mesure_time([&]() {
            if (_visible)
            {
                render(world, context);
            }
        });
    }
} // namespace core::systems
