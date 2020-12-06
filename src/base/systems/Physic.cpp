
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
        auto view = world.entities().view<Momentum, Position, Colider>();

        view.each([&](entt::entity entity, Momentum &momentum, Position &position, Colider &colider) {
            utils::Vec2f predicted = position() + utils::Vec2f{momentum.vx * dt, momentum.vy * dt};
            utils::Rectf predicted_colider = colider().offset(predicted);

            _entities.query_elements(predicted_colider.expended(core::Tile::SIZE), [&](const auto &other_position, const entt::entity &e) {
                if (e != entity && world.entities().has<Colider>(e))
                {
                    auto other_colider = world.entities().get<Colider>(e)();

                    utils::Rectf other_predicted_colider = other_colider.offset(other_position);

                    predicted = position() + utils::Vec2f{momentum.vx * dt, 0};
                    predicted_colider = colider().offset(predicted);

                    if (predicted_colider.colide_with(other_predicted_colider))
                    {
                        momentum.vx = 0;
                    }

                    predicted = position() + utils::Vec2f{0, momentum.vy * dt};
                    predicted_colider = colider().offset(predicted);

                    if (predicted_colider.colide_with(other_predicted_colider))
                    {
                        momentum.vy = 0;
                    }

                    predicted = position() + utils::Vec2f{momentum.vx * dt, momentum.vy * dt};
                    predicted_colider = colider().offset(predicted);

                    if (predicted_colider.colide_with(other_predicted_colider))
                    {
                        momentum.vx = 0;
                        momentum.vy = 0;
                    }
                }

                return utils::Iteration::CONTINUE;
            });
        });
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

            position.x = MAX(core::Tile::SIZE, MIN(world.terrain().bound().width() - core::Tile::SIZE, position.x));
            position.y = MAX(core::Tile::SIZE, MIN(world.terrain().bound().height() - core::Tile::SIZE, position.y));
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
