#pragma once

#include <imgui.h>

#include <entt.hpp>
#include <imgui.h>

template <typename TObject>
void inspect(TObject &)
{
    ImGui::Text("(The Object doesn't have an inspect() handler.)");
}

template <class TComponent>
void inspect_component(entt::registry &registry, entt::entity entity)
{
    auto &component = registry.get<TComponent>(entity);
    inspect(component);
}
