#include "DrinkSystem.h"

#include "game/components/Thirst.h"
#include "base/components/Position.h"

namespace game
{
    DrinkSystem::DrinkSystem(){}

    DrinkSystem::~DrinkSystem(){}

    void DrinkSystem::update(core::World &world, core::Time &time){
        auto player = world.entities().view<base::Position, game::Thirst>();

        player.each([&](auto &position, auto &thirst) {
            auto tx = position.x / core::Tile::SIZE;
            auto ty = position.y / core::Tile::SIZE;

            auto tile = world.terrain().tile(tx, ty);

            if (tile.flags & core::Tile::LIQUID)
            {
                if (thirst.current_thirst < thirst.max_thirst)
                {
                    thirst.current_thirst += 0.5f* time.elapsed();
                }
            }
            
        });
    }
} // namespace game
