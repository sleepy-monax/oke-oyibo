#pragma once

#include <raylib.h>

#include "systems/System.h"

#include "components/Position.h"

namespace systems
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

        virtual void render(world::World &world, loop::RenderContext &)
        {
            auto view = world.entities().view<components::Position>();

            view.each([](auto &position) {
                DrawCircle(position.x, position.y, 4, RED);
            });
        }
    };

} // namespace systems
