#include <raylib.h>

#include "core/World.h"

#include "core/Graphics.h"

#include "base/components/CastShadow.h"
#include "base/components/Position.h"
#include "base/systems/Shadow.h"

namespace base
{
    void Shadow::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<Position, CastShadow>();

        camera.with_shadows([&]() {
            ClearBackground(WHITE);

            view.each([](auto &position, auto &shadow) {
                core::draw_ellipse(position() + shadow.offset, shadow.size, shadow.size / 2.0f, {200, 200, 200, 255});
            });
        });
    }
} // namespace base