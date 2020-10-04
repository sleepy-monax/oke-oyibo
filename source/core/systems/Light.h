#pragma once

#include <raylib.h>

#include "core/components/LightSource.h"
#include "core/components/Position.h"
#include "core/systems/System.h"
#include "core/world/World.h"

namespace core::systems
{

    class Light : public System
    {
    private:
    public:
        Light() : System("Debug Render")
        {
        }

        ~Light() override
        {
        }

        void render(world::World &world, game::RenderContext &context) override
        {
            auto view = world.entities().view<components::Position, components::LightSource>();

            context.light().use_and_do([&]() {
                ClearBackground(BLACK);

                BeginBlendMode(BLEND_ADDITIVE);

                view.each([](auto &position, auto &light_source) {
                    DrawCircle(position.x, position.y, light_source.radius, light_source.color);
                });

                EndBlendMode();
            });
        }
    };

} // namespace core::systems