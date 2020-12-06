#include "game/systems/HungerSystem.h"

namespace game
{
    HungerSystem::HungerSystem()
    {
    }

    void HungerSystem::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<game::Hunger, game::Health, game::Stamina>();

        if (stackFrame(time))
        {
            view.each([&](auto &hunger, auto &health, auto &stamina) {
                if (stamina.current < (stamina.maximum) / 5)
                {
                    if (hunger.current_food - 0.5 <= 0)
                    {
                        hunger.current_food = 0;
                    }
                    else
                    {
                        hunger.current_food -= 0.5;
                    }
                }
                else
                {
                    if (hunger.current_food - 0.1 <= 0)
                    {
                        hunger.current_food = 0;
                    }
                    else
                    {
                        hunger.current_food -= 0.1;
                    }
                }

                if (hunger.current_food < (hunger.max_food / 4.0))
                {
                    health.current -= 0.1;
                }
            });
        }
    }

    bool HungerSystem::stackFrame(core::Time &time)
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

    void HungerSystem::on_load(core::Registry &registry)
    {
        foodTexture = registry.texture("food");
    }

    void HungerSystem::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Hunger>();

        camera.with_overlay([&]() {
            view.each([&](auto &position, auto &hunger) {
                utils::Rectf bound = {-15, -20, 30, 2};

                bound = bound.offset(position());
                bound = bound.take_left_percent(hunger.current_food / (float)hunger.max_food);

                core::fill_rect(bound, ORANGE);

                utils::Rectf foodRect = {-18, -20, 2, 2};
                foodRect = foodRect.offset(position());

                core::draw_texture(foodTexture, foodRect, WHITE);
            });
        });
    }
} // namespace game