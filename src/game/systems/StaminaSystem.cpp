#include "core/Graphics.h"
#include "core/Registry.h"

#include "base/components/Momentum.h"

#include "game/components/Stamina.h"

#include "game/systems/StaminaSystem.h"

namespace game
{
    void StaminaSystem::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<game::Stamina, base::Momentum>();

        if (stackFrame(time))
        {
            view.each([&](game::Stamina &stamina, base::Momentum &momentum) {
                if (momentum.ax == 0.05f || momentum.ay == 0.05f || momentum.ax == -0.05f || momentum.ay == -0.05f)
                {
                    if (stamina.current - 0.8f <= 0)
                    {
                        stamina.current = 0.0f;
                    }
                    else
                    {
                        stamina.current -= 0.8f;
                    }
                }

                if (momentum.ax == 0.0f && momentum.ay == 0.0f)
                {
                    if (stamina.current + 0.3f > stamina.maximum)
                    {
                        stamina.current = stamina.maximum;
                    }
                    else
                    {
                        stamina.current += 0.3f;
                    }
                }
            });
        }

        if (stackFrameForAcc(time))
        {
            view.each([&](game::Stamina &stamina, base::Momentum &momentum) {
                if (stamina.current < (stamina.maximum) / 5)
                {
                    if (momentum.ax == 0.05f)
                    {
                        momentum.ax = 0.02f;
                    }
                    else if (momentum.ay == 0.05f)
                    {
                        momentum.ay = 0.02f;
                    }
                    else if (momentum.ax == -0.05f)
                    {
                        momentum.ax = -0.02f;
                    }
                    else if (momentum.ay == -0.05f)
                    {
                        momentum.ay = -0.02f;
                    }
                }
            });
        }
    }

    bool StaminaSystem::stackFrame(core::Time &time)
    {
        _accumulator += time.elapsed();

        if (_accumulator >= 1)
        {
            _accumulator -= 1;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool StaminaSystem::stackFrameForAcc(core::Time &time)
    {
        _accumAccel += time.elapsed();

        if (_accumAccel >= 0.05)
        {
            _accumAccel -= 0.05;

            return true;
        }
        else
        {
            return false;
        }
    }

    void StaminaSystem::on_load(core::Registry &registry)
    {
        staminaTexture = registry.texture("stamina");
    }

    void StaminaSystem::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Stamina>();

        camera.with_overlay([&]() {
            view.each([&](auto &position, auto &stamina) {
                utils::Rectf bound = {-15, 5, 30, 2};

                bound = bound.offset(position());
                bound = bound.take_left_percent(stamina.current / (float)stamina.maximum);

                core::fill_rect(bound, YELLOW);

                utils::Rectf staminaRect = {-18, 4, 2, 2};
                staminaRect = staminaRect.offset(position());

                core::draw_texture(staminaTexture, staminaRect, WHITE);
            });
        });
    }
} // namespace game