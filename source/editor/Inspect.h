#pragma once

#include <imgui.h>

template <typename TObject>
static inline void inspect(TObject &)
{
    ImGui::Text("(The Object doesn't have an inspect() handler.)");
}
