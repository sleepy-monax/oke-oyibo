#include "HealthBar.h"

namespace game
{
    HealthBar::HealthBar()
    {
    }

    void HealthBar::update(core::World &world, core::Time &)
    {
        
        auto view = world.entities().view<Health>();
        view.each([](auto &damage, auto &health) {
            health.health -= damage;
            if(health.health<=0) health.health=0;
            if(health.health>=health.maxHealth) health.health=maxHealth;
        });
        
    }

    void HealthBar::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Health>();

        camera.with_overlay([&]() {
            view.each([](auto &position, auto &health) {
                DrawRectangle(position.x, position.y,((double) health.health/health.maxHealth)*100, 20, BLUE);
            });
        });
    }

} // namespace game
