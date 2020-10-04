#pragma once

#include <imgui.h>

#include <entt.hpp>
#include <imgui.h>

#include "core/world/World.h"

template <typename TObject>
static inline void inspect(TObject &)
{
    ImGui::Text("(The Object doesn't have an inspect() handler.)");
}

template <class TComponent>
void inspect_component(core::world::World &world, entt::entity entity)
{
    auto &component = world.entities().get<TComponent>(entity);
    inspect(component);
}

template <class TSystem>
void inspect_system(core::world::World &world, TSystem &system)
{
    __unused(world);
    inspect(system);
}
