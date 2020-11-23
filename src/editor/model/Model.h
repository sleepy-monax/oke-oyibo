#pragma once

#include "core/Probe.h"
#include "core/World.h"

#include "editor/FPSCounter.h"

namespace editor
{
    struct Model
    {
        entt::entity selected_entity;
        core::World &world;

        editor::FPSCounter fps{};

        core::Probe total_time{"Total"};
        core::Probe update_time{"Update"};
        core::Probe render_time{"Render"};
        core::Probe display_time{"Display"};

        Model(core::World &world) : world{world} {}

        auto &entities() { return world.entities(); }

        auto &registry() { return world.registry(); }

        auto &systems() { return world.systems(); }
    };
} // namespace editor
