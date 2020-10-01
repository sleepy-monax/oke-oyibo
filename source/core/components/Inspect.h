#pragma once

#include <entt.hpp>
#include <imgui.h>

#include "utils/Macros.h"

namespace core::components
{
    template <class TComponent>
    void inspect(entt::registry &registry, entt::entity entity)
    {
        __unused(registry);
        __unused(entity);

        ImGui::Text("(This component doesn't have an inspect() handler.)");
    }
} // namespace core::components
