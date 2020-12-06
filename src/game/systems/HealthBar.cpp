#include "core/Graphics.h"
#include "core/Registry.h"

#include "game/systems/HealthBar.h"

namespace game
{
    HealthBar::HealthBar()
    {
    }

    void HealthBar::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<Health>();
        view.each([&](entt::entity entity, auto &health) {
            if (health.current <= 0)
            {
                world.remove_entity(entity);
            }

            if (health.current >= health.maximum)
            {
                health.current = health.maximum;
            }

            health.current = health.current;
        });
    }

    void HealthBar::on_load(core::Registry &registry)
    {
        healthTexture = registry.texture("health");
    }

    void HealthBar::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Health>();

        camera.with_overlay([&]() {
            view.each([&](auto &position, auto &health) {
                if (health.current != health.maximum)
                {
                    utils::Rectf bound = {-15, -24, 30, 2};

                    bound = bound.offset(position());
                    bound = bound.take_left_percent(health.current / (float)health.maximum);

                    core::fill_rect(bound, RED);

                    utils::Rectf healthRect = {-18, -24, 2, 2};
                    healthRect = healthRect.offset(position());

                    core::draw_texture(healthTexture, healthRect, WHITE);
                }
            });
        });
    }

} // namespace game
