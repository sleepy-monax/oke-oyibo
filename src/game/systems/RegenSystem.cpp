#include "game/systems/RegenSystem.h"

namespace game
{
    RegenSystem::RegenSystem()
    {

    }

    void RegenSystem::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<game::Health, game::Hunger, game::Thirst>();

        if (stackFrame(time))
        {
            view.each([&](auto &health, auto &hunger, auto &thirst) {
                if ((thirst.current_thirst > (thirst.max_thirst*0.8)) && (hunger.current_food > (hunger.max_food*0.8)))
                {
                    if (health.health + 1 > health.maxHealth) {
                        health.health = health.maxHealth;
                    } else {
                        health.health += 1;
                        thirst.current_thirst -= 0.3f;
                        hunger.current_food -= 0.3f;
                    } 
                }
            });
        }
    }

    bool RegenSystem::stackFrame(core::Time &time)
    {
        _accumulator += time.elapsed();

            if (_accumulator >= 3)
            {
                _accumulator -= 3;
                return true;
            }
            else
            {
                return false;
            }
    }
}