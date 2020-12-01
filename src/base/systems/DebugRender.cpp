#include "core/World.h"

#include <raylib.h>

#include "base/components/Position.h"
#include "base/systems/DebugRender.h"

namespace base
{
    void DebugRender::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position>();

        camera.with_overlay([&]() {
            view.each([](auto &position) {
                DrawCircle(position.x, position.y, 1, RED);
            });
        });
    }
} // namespace base