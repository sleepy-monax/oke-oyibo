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
        ThirstSystem() :
            System("ThirstSystem")
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
                    if ((thirst.current_thirst - 0.5) <= 0)
                    {
                        thirst.current_thirst = 0;
                    }
                    else
                    {
                        thirst.current_thirst -= 0.5;
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

        friend void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem);
    };
} // namespace game

template <>
inline void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem)
{
    ImGui::InputDouble("accumulator##ThirstSystem", &thirstSystem._accumulator);
}