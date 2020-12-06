#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "utils/Common.h"

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

    static inline bool Viewport(ImTextureID user_texture_id, const ImVec2 &size)
    {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
        {
            return false;
        }

        int id = window->GetID(user_texture_id);
        ImRect bb(window->Pos, window->Pos + size);
        ImGui::ItemSize(bb);

        if (!ItemAdd(bb, id, &bb))
        {
            return false;
        }

        ImGui::ItemHoverable(bb, id);

        window->DrawList->AddImage(user_texture_id, bb.Min, bb.Max, ImVec2(0, 0), ImVec2(1, 1), GetColorU32(ImVec4(1, 1, 1, 1)));

        return ImGui::IsItemHovered();
    }

    static inline void TextCenter(std::string text)
    {
        ImGui::Text(" ");

        float font_size = ImGui::GetFontSize() * text.size() / 2;
        ImGui::SameLine(
            ImGui::GetWindowSize().x / 2 -
            font_size + (font_size / 2));

        ImGui::Text(text.c_str());
    }
} // namespace ImGui
