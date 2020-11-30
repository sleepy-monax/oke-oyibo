#pragma once

#include <raylib.h>

#include "base/components/Position.h"
#include "core/System.h"
#include "core/World.h"

namespace base
{

    class DebugRender: public core::System
    {
    private:
    public:
        DebugRender()
        {
        }

        void render(core::World &world, core::Camera &camera) override
        {
            auto view = world.entities().view<base::Position>();

            camera.with_overlay([&]() {
                view.each([](auto &position) {
                    DrawCircle(position.x, position.y, 1, RED);
                });
            });
        }
    };

} // namespace base
