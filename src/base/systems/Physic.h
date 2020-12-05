#pragma once

#include "utils/QuadTree.h"

#include "core/System.h"
#include "editor/Inspect.h"

namespace base
{
    class Physic: public core::System
    {
        float _air_friction = 0.9;
        bool _show_quadtree = false;

        utils::QuadTree<float, entt::entity> _entities{utils::Rectf::empty()};

        void rebuild_quad_tree(core::World &world);

        void apply_acceleration(core::World &world, float dt);

        void check_for_colisions(core::World &world, float dt);

        void apply_friction(core::World &world, float dt);

        void apply_velocity(core::World &world, float dt);

        void update(core::World &world, core::Time &time) override;

        void render(core::World &world, core::Camera &camera) override;

        friend void inspect<base::Physic>(base::Physic &physic);
    };
} // namespace base

template <>
inline void inspect<base::Physic>(base::Physic &physic)
{
    ImGui::Checkbox("Show QuadTree", &physic._show_quadtree);
    ImGui::SliderFloat("Air Friction", &physic._air_friction, 0, 1, "Friction %f", 0);
}
