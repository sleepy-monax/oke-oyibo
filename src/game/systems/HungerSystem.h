#pragma once

#include <game/components/Health.h>
#include <game/components/Hunger.h>

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class HungerSystem: public core::System
    {
    private:
        double _accumulator = 0;

    public:
        HungerSystem()
        {
        }

        void update(core::World &world, core::Time &time)
        {
            auto view = world.entities().view<game::Hunger, game::Health>();

            if (stackFrame(time))
            {
                view.each([&](game::Hunger &hunger, game::Health &health) {
                    if ((hunger.current_food - 0.5) <= 0)
                    {
                        hunger.current_food = 0;
                    }
                    else
                    {
                        hunger.current_food -= 0.5;
                    }

                    if (hunger.current_food < (hunger.max_food / 3.0))
                    {
                        health.health -= 0.5;
                    }
                });
            }
        }

        bool stackFrame(core::Time &time)
        {
            _accumulator += time.elapsed();

            if (_accumulator >= 2)
            {
                _accumulator -= 2;
                return true;
            }
            else
            {
                return false;
            }
        }

        void render(core::World &world, core::Camera &camera)
        {
            auto view = world.entities().view<base::Position, Hunger>();

            camera.with_overlay([&]() {
                view.each([](auto &position, auto &hunger) {
                    utils::Rectf bound = {-15, -20, 30, 2};

                    bound = bound.offset(position.pos2d());
                    bound = bound.take_left_percent(hunger.current_food / (float)hunger.max_food);

                    core::fill_rect(bound, ORANGE);
                });
        });
    }

        friend void inspect<game::HungerSystem>(game::HungerSystem &hungerSystem);
    };
} // namespace game

template <>
inline void inspect<game::HungerSystem>(game::HungerSystem &hungerSystem)
{
    ImGui::InputDouble("accumulator##HungerSystem", &hungerSystem._accumulator);
}