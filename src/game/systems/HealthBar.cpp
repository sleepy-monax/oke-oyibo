#include "HealthBar.h"

namespace game
{
    HealthBar::HealthBar() :
        System("HealthBar")
    {
    }

    HealthBar::~HealthBar()
    {
    }

    void HealthBar::update()
    {
    }

    void HealthBar::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Position, Health>();

        camera.with_overlay([&]() {
            view.each([](auto &position, auto &) {
                DrawRectangle(position.x, position.y, 100, 20, BLUE);
            });
        });
    }

} // namespace game
