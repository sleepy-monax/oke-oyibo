#include "core/Graphics.h"

#include "game/systems/HealthBar.h"

namespace game
{
    HealthBar::HealthBar()
    {
    }

    void HealthBar::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Health>();
        view.each([](/*auto &damage,*/ auto &health) {
            //health.health -= damage;
            if (health.health <= 0)
            {
                health.health = 0;
            }
            if (health.health >= health.maxHealth)
            {
                health.health = health.maxHealth;
            }
            health.health = health.health;
        });
    }

    void HealthBar::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Health>();

        camera.with_overlay([&]() {
            view.each([](auto &position, auto &health) {
                utils::Rectf bound = {-15, -20, 30, 2};

                bound = bound.offset(position.pos2d());
                bound = bound.take_left_percent(health.health / (float)health.maxHealth);

                core::draw_rect(bound, RED);
            });
        });
    }

} // namespace game
