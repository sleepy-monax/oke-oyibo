#include "AttackSystem.h"

#include "base/components/Position.h"
#include "base/components/Player.h"

#include "game/components/Health.h"
#include "game/components/Enemy.h"

namespace game
{
    AttackSystem::AttackSystem() {}
    AttackSystem::~AttackSystem() {}

    void AttackSystem::update(core::World &world, core::Time &time)
    {
        if (stackFrame(time)) {
            auto enemy = world.entities().view<game::Enemy, base::Position, game::Health>();
            auto player = world.entities().view<base::Player, base::Position, game::Health>();

            enemy.each([&](auto const &entity, auto &, auto &positionEnemy, auto &healthEnemy)
            {
                auto enemy_pos = positionEnemy.pos2d();
                player.each([&](auto &, auto &positionPlayer, auto &healthPlayer)
                {
                    auto player_pos = positionPlayer.pos2d();

                    if (enemy_pos.distance_to(player_pos) <= 5) {
                        healthPlayer.health -= 0.5;
                        if (IsKeyPressed(KEY_F))
                        {
                            if (healthEnemy.health - 2 < 0){
                                world.remove_entity(entity);
                            } else {
                                healthEnemy.health -= 2;
                            }
                        }
                    }
                });
            });
        }
    }

    bool AttackSystem::stackFrame(core::Time &time)
    {
        _accumulator += time.elapsed();

            if (_accumulator >= 0.8)
            {
                _accumulator -= 0.8;
                return true;
            }
            else
            {
                return false;
            }
    }
}