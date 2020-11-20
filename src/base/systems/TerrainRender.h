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

                for (int x = 0; x < terrain.width(); x++)
                {
                    for (int y = 0; y < terrain.height(); y++)
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
