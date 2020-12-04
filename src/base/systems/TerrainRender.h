#pragma once

#include <raylib.h>

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/System.h"
#include "core/World.h"

namespace base
{
    class TerrainRender: public core::System
    {
    private:
    public:
        TerrainRender()
        {
        }

        void render(core::World &world, core::Camera &camera) override
        {
            camera.with_terrain([&]() {
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
                        core::draw_texture(world.terrain().tile(x, y).texture, {(float)x * core::Tile::SIZE, (float)y * core::Tile::SIZE, (float)core::Tile::SIZE, (float)core::Tile::SIZE}, WHITE);
                    }
                }
            });
        }
    };
} // namespace base
