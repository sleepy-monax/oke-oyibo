#include "game/generator/Pass.h"

namespace game
{
    class TilePass: public Pass
    {
        virtual void apply(core::World &world) final
        {
            for (int y = 0; y < world.terrain().width(); y++)
            {
                for (int x = 0; x < world.terrain().width(); x++)
                {

                    apply(world,
                          {
                              x * core::Tile::SIZE + core::Tile::SIZE / 2.f,
                              y * core::Tile::SIZE + core::Tile::SIZE / 2.f,
                          });
                }
            }
        }

        virtual void apply(core::World &, utils::Vec2f pos) {}
    };

} // namespace game
