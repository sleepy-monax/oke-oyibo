#pragma once

#include <raylib.h>

#include "base/components/Position.h"
#include "core/System.h"
#include "core/World.h"

namespace base
{

    class DebugRender : public core::System
    {
    private:
    public:
        DebugRender() : System("DebugRender")
        {
        }

        ~DebugRender() override
        {
        }

        void render(core::World &world, core::RenderContext &context) override
        {
            auto view = world.entities().view<base::Position>();

            context.overlay().use_and_do([&]() {
                view.each([](auto &position) {
                    DrawCircle(position.x, position.y, 4, RED);
                });
            });
        }
    };

} // namespace base
