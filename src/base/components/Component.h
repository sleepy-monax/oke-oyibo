#pragma once

#include "core/World.h"

template <class TComponent>
void inspect_component(core::World &world, entt::entity entity)
{
    auto &component = world.entities().get<TComponent>(entity);
    inspect(component);
}
