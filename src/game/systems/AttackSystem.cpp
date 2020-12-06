#include "AttackSystem.h"

#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"

#include "game/components/Attack.h"
#include "game/components/Enemy.h"
#include "game/components/Health.h"
#include "game/components/HoldItem.h"
#include "game/components/Inventory.h"

namespace game
{
    void AttackSystem::update(core::World &world, core::Time &time)
    {
        auto attackers = world.entities().view<base::Position, game::Attack>();

        attackers.each([&](entt::entity attacker, base::Position &attacker_position, game::Attack &attacker_attack) {
            attacker_attack.cooldown -= time.elapsed();

            int damages = attacker_attack.base_damages;

            auto victims = world.entities().view<base::Position, game::Health, base::Sprite>();

            if (attacker_attack.attacking && attacker_attack.cooldown < 0)
            {
                victims.each([&](entt::entity victim, base::Position &victim_position, game::Health &victim_health, base::Sprite &victim_sprite) {
                    if (attacker == victim)
                    {
                        return;
                    }

                    if (attacker_position().distance_to(victim_position()) <= attacker_attack.range * core::Tile::SIZE)
                    {
                        attacker_attack.cooldown = 0.8;
                        victim_sprite.flash = 0.1;
                        victim_health.current -= damages;

                        if (world.entities().has<base::Player>(victim))
                        {
                            auto &player = world.entities().get<base::Player>(victim);
                            auto &camera = world.players()[player.player_index].camera();

                            camera.trauma(0.1);
                        }
                    }
                });
            }

            attacker_attack.attacking = false;
        });
    }

} // namespace game