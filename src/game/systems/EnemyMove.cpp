#include <cmath>
#include <raylib.h>

#include "core/World.h"

#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/components/Position.h"

#include "game/components/Enemy.h"
#include "game/components/Prey.h"

#include "game/systems/EnemyMove.h"

namespace game
{

    //enemy movements
    void EnemyMove::update(core::World &world, core::Time &)
    {
        auto enemies = world.entities().view<game::Enemy, base::Position, base::Move>();

        enemies.each([&](game::Enemy &enemy, base::Position &enemy_position, base::Move &move) {
            auto preys = world.entities().view<game::Prey, base::Position>();

            preys.each([&](entt::entity entity, game::Prey &, base::Position &prey_position) {
                if (enemy.has_focus && enemy.target == entity)
                {
                    if (enemy_position.pos2d().distance_to(prey_position.pos2d()) > enemy.focus_distance * core::Tile::SIZE)
                    {
                        enemy.has_focus = false;
                        move.moving = false;
                    }
                    else
                    {
                        move.destination = prey_position.pos2d();
                        move.moving = true;
                    }
                }
                else if (enemy_position.pos2d().distance_to(prey_position.pos2d()) < enemy.focus_distance * core::Tile::SIZE)
                {
                    enemy.target = entity;
                    enemy.has_focus = true;
                    move.destination = prey_position.pos2d();
                    move.moving = true;
                }
            });

            if (!enemy.has_focus && !move.moving)
            {
                auto max_distance = enemy.wandering_distance * core::Tile::SIZE;

                auto multx = (_random.next_double() * 2) - 1;

                auto multy = (_random.next_double() * 2) - 1;

                auto offx = multx * max_distance;
                auto offy = multy * max_distance;

                move.destination = enemy_position.pos2d() + utils::Vec2f{(float)offx, (float)offy};
                move.moving = true;
            }
        });
    }
} // namespace game
