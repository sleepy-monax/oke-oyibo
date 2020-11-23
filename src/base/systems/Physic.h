#pragma once

#include "utils/QuadTree.h"

#include "core/System.h"
#include "core/World.h"

#include "base/components/Acceleration.h"
#include "base/components/Colider.h"
#include "base/components/Position.h"
#include "base/components/Velocity.h"

#include "editor/Inspect.h"

namespace base
{
    class Physic : public core::System
    {
    private:
        float _air_friction = 0.9;
        bool _show_quadtree = false;

        utils::QuadTree<float, entt::entity> _entities{utils::Rectf::empty()};

    public:
        Physic() : System("Physic")
        {
        }

        ~Physic()
        {
        }

        void rebuild_quad_tree(core::World &world)
        {
            _entities.clear_and_resize(world.terrain().bound());

            auto view = world.entities().view<Position>();

            for (auto entity : view)
            {
                auto &pos = view.get<Position>(entity);

                _entities.append({pos.x, pos.y}, entity);
            }
        }

        void apply_acceleration(core::World &world, float dt)
        {
            auto view = world.entities().view<Acceleration, Velocity>();

            view.each([&](auto &acceleration, auto &velocity) {
                velocity.vx += acceleration.ax * dt;
                velocity.vy += acceleration.ay * dt;

                acceleration.ax = 0;
                acceleration.ay = 0;
            });
        }

        void check_for_colisions(core::World &world, float dt)
        {
            __unused(world);
            __unused(dt);

            // FIXME: Implement colisions.
        }

        void apply_friction(core::World &world, float dt)
        {
            auto view = world.entities().view<Velocity>();

            view.each([&](auto &velocity) {
                velocity.vx -= (velocity.vx) * (1 - _air_friction) * dt;
                velocity.vy -= (velocity.vy) * (1 - _air_friction) * dt;
            });
        }

        void apply_velocity(core::World &world, float dt)
        {
            auto view = world.entities().view<Velocity, Position>();

            view.each([&](auto &velocity, auto &position) {
                position.x += velocity.vx * dt;
                position.y += velocity.vy * dt;
            });
        }

        void update(core::World &world, core::Time &time) override
        {
            auto dt = time.elapsed() * 60;

            rebuild_quad_tree(world);
            apply_acceleration(world, dt);
            check_for_colisions(world, dt);
            apply_friction(world, dt);
            apply_velocity(world, dt);
        }

        void render(core::World &world, core::Camera &camera) override
        {
            __unused(world);

            if (!_show_quadtree)
                return;

            camera.with_overlay([&]() {
                _entities.query_structure([](auto &rect) {
                    DrawRectangleLines(rect.x(), rect.y(), rect.width(), rect.height(), RED);
                    return utils::Iteration::CONTINUE;
                });
            });
        }

        friend void inspect<base::Physic>(base::Physic &physic);
    };
} // namespace base

template <>
inline void inspect<base::Physic>(base::Physic &physic)
{
    ImGui::Checkbox("Show QuadTree", &physic._show_quadtree);
    ImGui::SliderFloat("Air Friction", &physic._air_friction, 0, 1, "Friction %f", 0);
}
