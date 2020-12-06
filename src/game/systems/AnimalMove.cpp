#include "AnimalMove.h"

#include "base/components/Move.h"
#include "base/components/Position.h"
#include "game/components/Animal.h"

namespace game
{
    void AnimalMove::update(core::World &world, core::Time &)
    {
        auto animals = world.entities().view<game::Animal, base::Position, base::Move>();

        animals.each([&](game::Animal &animal, base::Position &enemy_position, base::Move &move) {
            if (!move.moving)
            {
                auto max_distance = animal.wandering_distance * core::Tile::SIZE;

                auto multx = (_random.next_double() * 2) - 1;

                auto multy = (_random.next_double() * 2) - 1;

                auto offx = multx * max_distance;
                auto offy = multy * max_distance;

                auto pos = enemy_position() + utils::Vec2f{(float)offx, (float)offy};

                // Prevent entities escaping their natural environement.
                auto tx = pos.x() / core::Tile::SIZE;
                auto ty = pos.y() / core::Tile::SIZE;

                if (world.terrain().bound().contains(pos))
                {
                    auto tile = world.terrain().tile(tx, ty);

                    if (tile.flags & core::Tile::LIQUID)
                        return;
                }

                move.move_to(pos);
            }
        });
    }
} // namespace game
