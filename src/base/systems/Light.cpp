#include <raylib.h>

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
            ClearBackground(GRAY);

            BeginBlendMode(BLEND_ADDITIVE);

            view.each([](auto &position, auto &light_source) {
                DrawCircle(position.x, position.y, light_source.radius, light_source.color);
            });

            EndBlendMode();
        });
    }
} // namespace base