#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include <cstdint>
#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
    static inline void Help(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    static inline bool SliderUint8(const char *label, uint8_t *v, uint8_t v_min, uint8_t v_max, const char *format = "%d", ImGuiSliderFlags flags = 0)
    {
        return SliderScalar(label, ImGuiDataType_U8, v, &v_min, &v_max, format, flags);
    }

    static inline void Viewport(ImTextureID user_texture_id, const ImVec2 &size)
    {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
            return;
        ImRect bb(window->Pos, window->Pos + size);
        window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, ImVec2(0, 0), ImVec2(1, 1), GetColorU32(ImVec4(1, 1, 1, 1)));
    }
} // namespace ImGui
