#include "AttackSystem.h"

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "game/components/Attack.h"
#include "game/components/Enemy.h"
#include "game/components/Health.h"
#include "game/components/HoldItem.h"
#include "game/components/Inventory.h"

namespace game
{
    void AttackSystem::update(core::World &world, core::Time &time)
    {
        if (stackFrame(time))
        {
            auto enemy = world.entities().view<game::Enemy, base::Position, game::Health, game::Attack>();
            auto player = world.entities().view<base::Player, base::Position, game::Health, game::Inventory, game::HoldItem, game::Attack>();

            enemy.each([&](auto const &entity, auto &, auto &positionEnemy, auto &health_enemy, auto &attackEnemy) {
                auto enemy_pos = positionEnemy.pos2d();

                player.each([&](auto &, auto &positionPlayer, auto &health_player, auto &inv, auto &hold, auto &attackPlayer) {
                    auto player_pos = positionPlayer.pos2d();

                    if (enemy_pos.distance_to(player_pos) <= 5)
                    {
                        health_player.current -= attackEnemy.attack;

                        if (IsKeyPressed(KEY_F))
                        {
                            string holdItem = inv.inventory[hold.index].getItem().getName();

                            if (holdItem == "sword")
                            {
                                attackPlayer.attack = 5;
                            }
                            if (health_enemy.current - attackPlayer.attack < 0)
                            {
                                world.remove_entity(entity);
                            }
                            else
                            {
                                health_enemy.current -= attackPlayer.attack;
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
} // namespace game