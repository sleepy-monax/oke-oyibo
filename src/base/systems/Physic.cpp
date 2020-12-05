
#include "core/World.h"

#include "base/components/Colider.h"
#include "base/components/Momentum.h"
#include "base/components/Position.h"

#include "base/systems/Physic.h"

namespace base
{
    void Physic::rebuild_quad_tree(core::World &world)
    {
        _entities.clear_and_resize(world.terrain().bound());

        auto view = world.entities().view<Position>();

        for (auto entity : view)
        {
            auto &pos = view.get<Position>(entity);

            _entities.append({pos.x, pos.y}, entity);
        }
    }

    void Physic::apply_acceleration(core::World &world, float dt)
    {
        auto view = world.entities().view<Momentum>();

        view.each([&](auto &momentum) {
            momentum.vx += momentum.ax * dt;
            momentum.vy += momentum.ay * dt;

            momentum.ax = 0;
            momentum.ay = 0;
        });
    }

    void Physic::check_for_colisions(core::World &world, float dt)
    {
        __unused(world);
        __unused(dt);

        // FIXME: Implement colisions.
    }

    void Physic::apply_friction(core::World &world, float dt)
    {
        auto view = world.entities().view<Momentum>();

        view.each([&](auto &momentum) {
            momentum.vx -= (momentum.vx) * (1 - _air_friction) * dt;
            momentum.vy -= (momentum.vy) * (1 - _air_friction) * dt;
        });
    }

    void Physic::apply_velocity(core::World &world, float dt)
    {
        auto view = world.entities().view<Momentum, Position>();

        view.each([&](auto &momentum, auto &position) {
            position.x += momentum.vx * dt;
            position.y += momentum.vy * dt;

            position.x = MAX(0, MIN(world.terrain().bound().width(), position.x));
            position.y = MAX(0, MIN(world.terrain().bound().height(), position.y));
        });
    }

    void Physic::update(core::World &world, core::Time &time)
    {
        auto dt = time.elapsed() * 60;

        rebuild_quad_tree(world);
        apply_acceleration(world, dt);
        check_for_colisions(world, dt);
        apply_friction(world, dt);
        apply_velocity(world, dt);
    }

    void Physic::render(core::World &world, core::Camera &camera)
    {
        __unused(world);

        if (!_show_quadtree)
        {
            return;
        }

        camera.with_overlay([&]() {
            _entities.query_structure([](auto &rect) {
                DrawRectangleLines(rect.x(), rect.y(), rect.width(), rect.height(), RED);
                return utils::Iteration::CONTINUE;
            });
        });
    }

} // namespace base
