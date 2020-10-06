#pragma once

#include "core/world/World.h"

template <class TComponent>
void inspect_component(core::world::World &world, entt::entity entity)
{
    auto &component = world.entities().get<TComponent>(entity);
    inspect(component);
}
