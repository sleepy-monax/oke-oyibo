#pragma once

#include <imgui.h>

#include "render/Target.h"

namespace game
{
    class RenderContext
    {
    private:
        render::Target _terrain{};
        render::Target _shadows{};
        render::Target _light{};
        render::Target _entities{};
        render::Target _overlay{};

        render::Target _composite{};

    public:
        render::Target &terrain() { return _terrain; }
        render::Target &shadows() { return _shadows; }
        render::Target &light() { return _light; }
        render::Target &entities() { return _entities; }
        render::Target &overlay() { return _overlay; }
        render::Target &composite() { return _composite; }

        RenderContext() {}

        template <typename TCallback>
        void use_and_do(TCallback callback)
        {
            _terrain.resize_to_fit_the_screen();
            _shadows.resize_to_fit_the_screen();
            _light.resize_to_fit_the_screen();
            _entities.resize_to_fit_the_screen();
            _overlay.resize_to_fit_the_screen();
            _composite.resize_to_fit_the_screen();

            callback();
        }

        void display()
        {
            ImGui::Begin("Render Context");

            ImGui::Text("Terrain Map");
            _terrain.display();
            ImGui::Separator();

            ImGui::Text("Shadow Map");
            _shadows.display();
            ImGui::Separator();

            ImGui::Text("Light Map");
            _light.display();
            ImGui::Separator();

            ImGui::Text("Entities Map");
            _entities.display();
            ImGui::Separator();

            ImGui::Text("Overlay Map");
            _overlay.display();
            ImGui::Separator();

            ImGui::Text("Final Result");
            _overlay.display();
            ImGui::Separator();

            ImGui::End();
        }
    };
} // namespace game
