#pragma once

#include "editor/Panel.h"

namespace editor
{
    class Viewport: public Panel
    {
    private:
        int _width = 128;
        int _height = 128;

        core::Camera _camera{};

    public:
        Viewport()
        {
            name("Viewport");
            _camera.speed(30);
        }

        ~Viewport() override
        {
        }

        void update(Model &, core::Time &time) override
        {
            _camera.resize_to_fit(_width, _height);
            _camera.animate(time.elapsed());
        }

        void render(Model &model) override
        {
            _camera.clear();
            model.world->render(_camera);
            _camera.compose();
        }

        void display(Model &) override
        {
            auto size = ImGui::GetWindowSize();

            _width = size.x;
            _height = size.y - 4;

            auto viewport_focused = ImGui::Viewport(reinterpret_cast<void *>(_camera.composite().underlying_texture().id), ImVec2(_camera.composite().width(), _camera.composite().height()));

            if (viewport_focused)
            {
                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
                {
                    auto vec = ImGui::GetMouseDragDelta();
                    ImGui::ResetMouseDragDelta();

                    _camera.move({-vec.x / _camera.zoom(), -vec.y / _camera.zoom()});
                }

                float v = ImGui::GetIO().MouseWheel;

                if (v < 0)
                {
                    _camera.zoom_out();
                }
                else if (v > 0)
                {
                    _camera.zoom_in();
                }
            }
        }
    };
} // namespace editor
