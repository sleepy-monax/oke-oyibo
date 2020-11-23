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

        void render(core::World &world, core::Camera &camera) override
        {
            camera.terrain().use_and_do([&]() {
                auto &terrain = world.terrain();

                utils::Rectf bound = camera.bound_world();

                for (int x = MAX(0, bound.left() / core::Tile::SIZE);
                     x < MIN(bound.right() / core::Tile::SIZE, terrain.width());
                     x++)
                {
                    for (int y = MAX(0, bound.top() / core::Tile::SIZE);
                         y < MIN(bound.bottom() / core::Tile::SIZE, terrain.height());
                         y++)
                    {
                        DrawRectangleLines(
                            x * core::Tile::SIZE,
                            y * core::Tile::SIZE,
                            core::Tile::SIZE,
                            core::Tile::SIZE,
                            GREEN);
                    }
                }
            });
        }
    };
} // namespace base
