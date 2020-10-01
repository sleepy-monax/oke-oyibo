#pragma once

#include <raylib.h>

#include "systems/System.h"
#include "world/World.h"

namespace systems
{
    class TerrainRender : public System
    {
    private:
    public:
        TerrainRender() : System("Terrain Render") {}

        void render(world::World &world, game::RenderContext &context) override
        {
            context.terrain().use_and_do([&]() {
                auto &terrain = world.terrain();

                for (int x = 0; x < terrain.width(); x++)
                {
                    for (int y = 0; y < terrain.height(); y++)
                    {
                        DrawRectangleLines(x, y, 1, 1, RED);
                    }
                }
            });
        }
    };
} // namespace systems
