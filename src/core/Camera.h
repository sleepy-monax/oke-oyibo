#pragma once

#include "core/Surface.h"
#include "utils/Math.h"
#include "utils/Rect.h"

namespace core
{
    class CameraState
    {
    private:
        float _x;
        float _y;
        float _zoom;

    public:
        float x() const { return _x; }
        float y() const { return _y; }
        float zoom() const { return _zoom; }

        CameraState zoomed_in()
        {
            CameraState copy = *this;
            copy._zoom *= 2;
            return copy;
        }

        CameraState zoomed_out()
        {
            CameraState copy = *this;
            copy._zoom /= 2;
            return copy;
        }

        CameraState moved_to(float x, float y)
        {
            CameraState copy = *this;
            copy._x = x;
            copy._y = y;
            return copy;
        }

        CameraState() : _x(0), _y(0), _zoom(1)
        {
        }

        CameraState(float x, float y, float zoom) : _x(x), _y(y), _zoom(zoom)
        {
        }
    };

    static inline CameraState lerp(const CameraState from, const CameraState to, float t)
    {
        return {
            utils::lerp(from.x(), to.x(), t),
            utils::lerp(from.y(), to.y(), t),
            utils::lerp(from.zoom(), to.zoom(), t),
        };
    }

    class Camera
    {
    private:
        float _speed = 1;
        int _width = 0;
        int _height = 0;

        CameraState _current = {};
        CameraState _target = {};

        Surface _terrain{};
        Surface _shadows{};
        Surface _light{};
        Surface _entities{};
        Surface _overlay{};

        Surface _composite{};

    public:
        auto width() { return _width / _current.zoom(); }
        auto height() { return _height / _current.zoom(); }
        utils::Vec2f position() { return {_current.x(), _current.y()}; }
        utils::Vec2f size() { return {width(), height()}; }
        utils::Rectf bound()
        {
            return {position() - size() / 2, size()};
        }

        Camera2D raylib_camera()
        {
            return {
                {0, 0},
                {position().x(), position().y()},
                0,
                _current.zoom(),
            };
        }

        void speed(float speed)
        {
            _speed = speed;
        }

        CameraState current() { return _current; }

        CameraState target() { return _target; }

        Surface &terrain() { return _terrain; }
        Surface &shadows() { return _shadows; }
        Surface &light() { return _light; }
        Surface &entities() { return _entities; }
        Surface &overlay() { return _overlay; }

        Surface &composite() { return _composite; }

        Camera()
        {
            _width = GetScreenWidth();
            _height = GetScreenHeight();
        }

        void resize_to_fit(int width, int height)
        {
            _terrain.resize_to_fit(width, height);
            _shadows.resize_to_fit(width, height);
            _light.resize_to_fit(width, height);
            _entities.resize_to_fit(width, height);
            _overlay.resize_to_fit(width, height);
            _composite.resize_to_fit(width, height);

            _width = width;
            _height = height;
        }

        void resize_to_fit_the_screen()
        {
            resize_to_fit(GetScreenWidth(), GetScreenHeight());
        }

        void clear()
        {
            _terrain.use_and_do([]() {
                ClearBackground(BLACK);
            });

            _shadows.use_and_do([]() {
                ClearBackground({});
            });

            _entities.use_and_do([]() {
                ClearBackground({});
            });

            _overlay.use_and_do([]() {
                ClearBackground({});
            });
        }

        void compose()
        {
            composite().use_and_do([&]() {
                Rectangle rect{0, 0, (float)width(), (float)height()};
                DrawTexturePro(terrain().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(shadows().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(entities().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);

                BeginBlendMode(BLEND_MULTIPLIED);
                DrawTexturePro(light().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                EndBlendMode();

                DrawTexturePro(overlay().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            });
        }

        void display()
        {
            ImGui::Begin("Render Context");

            ImGui::Text("Terrain Map");
            _terrain.display(1 / 6.0);
            ImGui::Separator();

            ImGui::Text("Shadow Map");
            _shadows.display(1 / 6.0);
            ImGui::Separator();

            ImGui::Text("Light Map");
            _light.display(1 / 6.0);
            ImGui::Separator();

            ImGui::Text("Entities Map");
            _entities.display(1 / 6.0);
            ImGui::Separator();

            ImGui::Text("Overlay Map");
            _overlay.display(1 / 6.0);
            ImGui::Separator();

            ImGui::Text("Final Result");
            _composite.display(1 / 6.0);
            ImGui::Separator();

            ImGui::End();
        }

        void zoom_in()
        {
            _target = _target.zoomed_in();
        }

        void zoom_out()
        {
            _target = _target.zoomed_out();
        }

        void move_to(double x, double y)
        {
            _target = _target.moved_to(x, y);
        }

        void jump_to(double x, double y)
        {
            _target = _target.moved_to(x, y);
            _current = _current.moved_to(x, y);
        }

        void animate(double dt)
        {
            _current = lerp(_current, _target, dt);
        }
    };
} // namespace core
