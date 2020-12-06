#pragma once

#include "core/Surface.h"
#include "utils/Math.h"
#include "utils/Random.h"
#include "utils/Rect.h"
#include "utils/Vec.h"

namespace core
{
    class CameraState
    {
    private:
        utils::Vec2f _position;
        float _zoom;
        float _trauma = 0;

    public:
        utils::Vec2f position() const { return _position; }
        float zoom() const { return _zoom; }
        float trauma() const { return _trauma; }

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

        CameraState moved_to(utils::Vec2f position)
        {
            CameraState copy = *this;
            copy._position = position;
            return copy;
        }

        CameraState move(utils::Vec2f position)
        {
            CameraState copy = *this;
            copy._position += position;
            return copy;
        }

        CameraState trauma(float value)
        {
            CameraState copy = *this;
            copy._trauma += value;
            return copy;
        }

        CameraState() :
            _position{0, 0}, _zoom(4)
        {
        }

        CameraState(utils::Vec2f position, float zoom, float trauma) :
            _position{position}, _zoom(zoom), _trauma(trauma)
        {
        }
    };

    static inline CameraState lerp(const CameraState from, const CameraState to, float t)
    {
        return {
            utils::lerp(from.position(), to.position(), t),
            utils::lerp(from.zoom(), to.zoom(), t),
            utils::lerp(from.trauma(), to.trauma(), t),
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
        utils::Random _random{};

    public:
        auto zoom() { return _current.zoom(); }
        auto width() { return _width; }
        auto height() { return _height; }
        auto width_world() { return _width / _current.zoom(); }
        auto height_world() { return _height / _current.zoom(); }

        auto position() { return _current.position(); }
        utils::Vec2f size_world() { return {width_world(), height_world()}; }
        utils::Rectf bound_world()
        {
            return {position() - size_world() / 2, size_world()};
        }

        Camera2D raylib_camera()
        {
            return {
                {width() / 2.0f, height() / 2.0f},
                {position().x() + 16 * (float)_random.next_double_minus_one_to_one() * _current.trauma(),
                 position().y() + 16 * (float)_random.next_double_minus_one_to_one() * _current.trauma()},
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

        template <typename TCallback>
        void use_and_do(TCallback callback)
        {
            BeginMode2D(raylib_camera());
            callback();
            EndMode2D();
        }

        template <typename TCallback>
        void with_terrain(TCallback callback)
        {
            _terrain.use_and_do([&]() {
                use_and_do(callback);
            });
        }

        template <typename TCallback>
        void with_shadows(TCallback callback)
        {
            _shadows.use_and_do([&]() {
                use_and_do(callback);
            });
        }

        template <typename TCallback>
        void with_light(TCallback callback)
        {
            _light.use_and_do([&]() {
                use_and_do(callback);
            });
        }

        template <typename TCallback>
        void with_entities(TCallback callback)
        {
            _entities.use_and_do([&]() {
                use_and_do(callback);
            });
        }

        template <typename TCallback>
        void with_overlay(TCallback callback)
        {
            _overlay.use_and_do([&]() {
                use_and_do(callback);
            });
        }

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
            _composite.use_and_do([]() {
                ClearBackground(BLANK);
            });

            _terrain.use_and_do([]() {
                ClearBackground(BLANK);
            });

            _shadows.use_and_do([]() {
                ClearBackground(BLANK);
            });

            _entities.use_and_do([]() {
                ClearBackground(BLANK);
            });

            _overlay.use_and_do([]() {
                ClearBackground(BLANK);
            });
        }

        void compose()
        {
            composite().use_and_do([&]() {
                Rectangle rect{0, 0, (float)width(), (float)height()};
                DrawTexturePro(terrain().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);

                BeginBlendMode(BLEND_MULTIPLIED);
                DrawTexturePro(shadows().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                EndBlendMode();

                DrawTexturePro(entities().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);

                BeginBlendMode(BLEND_MULTIPLIED);
                DrawTexturePro(light().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                EndBlendMode();

                DrawTexturePro(overlay().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            });
        }

        void zoom_in()
        {
            _target = _target.zoomed_in();
        }

        void zoom_out()
        {
            _target = _target.zoomed_out();
        }

        void move_to(utils::Vec2f pos)
        {
            _target = _target.moved_to(pos);
        }

        void move(utils::Vec2f pos)
        {
            _target = _target.move(pos);
        }

        void jump_to(utils::Vec2f pos)
        {
            _target = _target.moved_to(pos);
            _current = _current.moved_to(pos);
        }

        void trauma(float value)
        {
            _current = _current.trauma(value);
        }

        void animate(double dt)
        {
            // Integrate in order to prevent funky movement on slow systems.
            while (dt > 1 / 100.0)
            {
                _current = lerp(_current, _target, (1 / 100.0) * _speed);
                dt -= 1 / 100.;
            }

            _current = lerp(_current, _target, dt * _speed);
        }
    };
} // namespace core
