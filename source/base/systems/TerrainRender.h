#pragma once

#include <raylib.h>

#include "core/System.h"
#include "core/World.h"

namespace base
{
    class TerrainRender : public core::System
    {
    private:
    public:
        TerrainRender() : System("Terrain Render") {}

        void render(core::World &world, core::RenderContext &context) override
        {
            context.terrain().use_and_do([&]() {
                auto &terrain = world.terrain();

                for (int x = 0; x < terrain.width(); x++)
                {
                    for (int y = 0; y < terrain.height(); y++)
                    {
                        DrawRectangleLines(x, y, 1, 1, GREEN);
                    }
                }
            });
        }
    };
} // namespace base
