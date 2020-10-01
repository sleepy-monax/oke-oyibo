#pragma once

#include <raylib.h>

#include "core/systems/System.h"

#include "core/components/Position.h"

namespace core::systems
{

    class DebugRender : public System
    {
    private:
    public:
        DebugRender() : System("Debug Render")
        {
        }

        ~DebugRender() override
        {
        }

        virtual void render(world::World &world, game::RenderContext &)
        {
            auto view = world.entities().view<components::Position>();

            view.each([](auto &position) {
                DrawCircle(position.x, position.y, 4, RED);
            });
        }
    };

} // namespace core::systems
