#pragma once

#include <game/components/Health.h>
#include <game/components/Thirst.h>

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class ThirstSystem: public core::System
    {
    private:
        double _accumulator = 0;

    public:
        ThirstSystem()
        {
        }

        ~ThirstSystem() override
        {
        }

        void update(core::World &world, core::Time &time)
        {
            auto view = world.entities().view<game::Thirst, game::Health>();

            if (stackFrame(time))
            {
                view.each([&](game::Thirst &thirst, game::Health &health) {
                    if ((thirst.current_thirst - 0.3) <= 0)
                    {
                        thirst.current_thirst = 0;
                    }
                    else
                    {
                        thirst.current_thirst -= 0.3;
                    }

                    if (thirst.current_thirst < (thirst.max_thirst / 3.0))
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
            auto view = world.entities().view<base::Position, Thirst>();

            camera.with_overlay([&]() {
                view.each([](auto &position, auto &thirst) {
                    utils::Rectf bound = {-15, -22, 30, 2};

                    bound = bound.offset(position.pos2d());
                    bound = bound.take_left_percent(thirst.current_thirst / (float)thirst.max_thirst);

                    core::fill_rect(bound, BLUE);
                });
        });
    }

        friend void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem);
    };
} // namespace game

template <>
inline void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem)
{
    ImGui::InputDouble("accumulator##ThirstSystem", &thirstSystem._accumulator);
}