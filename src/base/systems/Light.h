#pragma once

#include <raylib.h>

#include "base/components/LightSource.h"
#include "base/components/Position.h"
#include "core/System.h"
#include "core/World.h"

namespace base
{

    class Light : public core::System
    {
    private:
    public:
        Light() : System("Debug Render")
        {
        }

        void render(core::World &world, core::Camera &context) override
        {
            auto view = world.entities().view<Position, LightSource>();

            context.light().use_and_do([&]() {
                ClearBackground(GRAY);

                BeginBlendMode(BLEND_ADDITIVE);

                view.each([](auto &position, auto &light_source) {
                    DrawCircle(position.x, position.y, light_source.radius, light_source.color);
                });

                EndBlendMode();
            });
        }
    };

} // namespace base