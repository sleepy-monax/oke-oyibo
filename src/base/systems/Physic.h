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
        float _time_scale = 1 / 60.0;
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

        void apply_acceleration(core::World &world, core::UpdateContext &context)
        {
            auto view = world.entities().view<Acceleration, Velocity>();

            view.each([&](auto &acceleration, auto &velocity) {
                velocity.vx += acceleration.ax * (context.elapsed_time() / _time_scale);
                velocity.vy += acceleration.ay * (context.elapsed_time() / _time_scale);

                acceleration.ax = 0;
                acceleration.ay = 0;
            });
        }

        void check_for_colisions(core::World &world, core::UpdateContext &context)
        {
            __unused(world);
            __unused(context);

            // FIXME: Implement colisions.
        }

        void apply_friction(core::World &world, core::UpdateContext &context)
        {
            auto view = world.entities().view<Velocity>();

            view.each([&](auto &velocity) {
                velocity.vx *= (1 - _air_friction) * (context.elapsed_time() / _time_scale);
                velocity.vy *= (1 - _air_friction) * (context.elapsed_time() / _time_scale);
            });
        }

        void apply_velocity(core::World &world, core::UpdateContext &context)
        {
            auto view = world.entities().view<Velocity, Position>();

            view.each([&](auto &velocity, auto &position) {
                position.x += velocity.vx * (context.elapsed_time() / _time_scale);
                position.y += velocity.vy * (context.elapsed_time() / _time_scale);
            });
        }

        void update(core::World &world, core::UpdateContext &context) override
        {
            rebuild_quad_tree(world);
            apply_acceleration(world, context);
            check_for_colisions(world, context);
            apply_friction(world, context);
            apply_velocity(world, context);
        }

        void render(core::World &world, core::RenderContext &context) override
        {
            __unused(world);

            if (!_show_quadtree)
                return;

            context.overlay().use_and_do([&]() {
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
void inspect<base::Physic>(base::Physic &physic)
{
    ImGui::Checkbox("Show QuadTree", &physic._show_quadtree);
    ImGui::SliderFloat("Air Friction", &physic._air_friction, 0, 1, "Friction %f", 0);
    ImGui::SliderFloat("Time step", &physic._time_scale, 0, 1, "%fsec", 0);
}
