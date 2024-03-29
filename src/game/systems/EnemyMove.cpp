#include <cmath>
#include <raylib.h>

#include "core/World.h"

#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/components/Position.h"

#include "game/components/Attack.h"
#include "game/components/Enemy.h"
#include "game/components/Prey.h"

#include "game/systems/EnemyMove.h"

namespace game
{

    //enemy movements
    void EnemyMove::update(core::World &world, core::Time &)
    {
        auto enemies = world.entities().view<game::Enemy, base::Position, base::Move, game::Attack>();

        enemies.each([&](game::Enemy &enemy, base::Position &enemy_position, base::Move &move, game::Attack &attack) {
            auto preys = world.entities().view<game::Prey, base::Position>();

            preys.each([&](entt::entity entity, game::Prey &, base::Position &prey_position) {
                double distance = enemy_position().distance_to(prey_position());

                if (enemy.has_focus && enemy.target == entity)
                {
                    if (!world.entities().valid(entity) ||
                        distance > enemy.focus_distance * core::Tile::SIZE)
                    {
                        enemy.has_focus = false;
                        move.stop();
                    }
                    else
                    {
                        move.move_to(prey_position());

                        if (distance < core::Tile::SIZE)
                        {
                            attack.attacking = true;
                        }
                    }
                }
                else if (distance < enemy.focus_distance * core::Tile::SIZE)
                {
                    enemy.target = entity;
                    enemy.has_focus = true;

                    move.move_to(prey_position());
                }

                if (enemy.target == entity && enemy.has_focus)
                {
                    auto tx = prey_position.x / core::Tile::SIZE;
                    auto ty = prey_position.y / core::Tile::SIZE;

                    auto prey_tile = world.terrain().tile(tx, ty);

                    if (enemy.isWaterCreature)
                    {

                        if (!(prey_tile.flags & core::Tile::LIQUID))
                        {
                            enemy.has_focus = false;
                            move.stop();
                        }
                    }
                    else
                    {
                        if (prey_tile.flags & core::Tile::LIQUID)
                        {
                            enemy.has_focus = false;
                            move.stop();
                        }
                    }
                }
            });

            if (!enemy.has_focus && !move.moving)
            {
                auto max_distance = enemy.wandering_distance * core::Tile::SIZE;

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

                    if (enemy.isWaterCreature)
                    {
                        if (!(tile.flags & core::Tile::LIQUID))
                            return;
                    }
                    else
                    {
                        if (tile.flags & core::Tile::LIQUID)
                            return;
                    }
                }

                if (!move.moving)
                {
                    move.move_to(pos);
                }
            }
        });
    }
} // namespace game
