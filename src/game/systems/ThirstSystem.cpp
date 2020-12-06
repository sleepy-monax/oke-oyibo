#include "game/systems/ThirstSystem.h"

#include "base/components/Position.h"
#include "game/components/Stamina.h"

namespace game
{
    ThirstSystem::ThirstSystem() {}

    ThirstSystem::~ThirstSystem() {}

    void ThirstSystem::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<game::Thirst, game::Health, game::Stamina>();

        if (stackFrame(time))
        {
            view.each([&](auto &thirst, auto &health, auto &stamina) {
                if (stamina.current <= stamina.maximum / 5)
                {
                    if (thirst.current_thirst - 0.4 <= 0)
                    {
                        thirst.current_thirst = 0;
                    }
                    else
                    {
                        thirst.current_thirst -= 0.4;
                    }
                }
                else
                {
                    if ((thirst.current_thirst - 0.1) <= 0)
                    {
                        thirst.current_thirst = 0;
                    }
                    else
                    {
                        thirst.current_thirst -= 0.1;
                    }
                }
                if (thirst.current_thirst < (thirst.max_thirst / 4.0))
                {
                    health.current -= 0.2;
                }
            });
        }
    }

    bool ThirstSystem::stackFrame(core::Time &time)
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

    void ThirstSystem::on_load(core::Registry &registry)
    {
        waterTexture = registry.texture("water");
    }

    void ThirstSystem::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Thirst>();

        camera.with_overlay([&]() {
            view.each([&](auto &position, auto &thirst) {
                utils::Rectf bound = {-15, -22, 30, 2};

                bound = bound.offset(position());
                bound = bound.take_left_percent(thirst.current_thirst / (float)thirst.max_thirst);

                core::fill_rect(bound, BLUE);

                utils::Rectf waterRect = {-18, -22, 2, 2};
                waterRect = waterRect.offset(position());

                core::draw_texture(waterTexture, waterRect, WHITE);
            });
        });
    }
} // namespace game
