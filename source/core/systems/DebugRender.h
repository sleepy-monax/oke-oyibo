#pragma once

#include <raylib.h>

#include "core/components/Position.h"
#include "core/systems/System.h"
#include "core/world/World.h"

namespace core::systems
{

    class DebugRender : public System
    {
    private:
    public:
        DebugRender() : System("DebugRender")
        {
        }

        ~DebugRender() override
        {
        }

        void render(world::World &world, game::RenderContext &context) override
        {
            auto view = world.entities().view<components::Position>();

            context.overlay().use_and_do([&]() {
                view.each([](auto &position) {
                    DrawCircle(position.x, position.y, 4, RED);
                });
            });
        }
    };

} // namespace core::systems
