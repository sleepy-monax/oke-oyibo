#include <raylib.h>

#include "core/Graphics.h"
#include "core/World.h"

#include "base/components/LightSource.h"
#include "base/components/Position.h"
#include "base/systems/Light.h"

namespace base
{
    void Light::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<Position, LightSource>();

        camera.with_light([&]() {
            ClearBackground(WHITE); // FIXME: day night cycle.

            BeginBlendMode(BLEND_ADDITIVE);

            view.each([](auto &position, auto &light_source) {
                core::draw_ellipse(position(), light_source.radius, light_source.radius, light_source.color);
            });

            EndBlendMode();
        });
    }
} // namespace base