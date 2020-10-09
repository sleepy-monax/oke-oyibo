#pragma once

#include "utils/Math.h"

namespace core::render
{
    class CameraState
    {
    private:
        double _x;
        double _y;
        double _zoom;

    public:
        double x() const { return _x; }
        double y() const { return _y; }
        double zoom() const { return _zoom; }

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

        CameraState moved_to(double x, double y)
        {
            CameraState copy = *this;
            copy._x = x;
            copy._y = y;
            return copy;
        }

        CameraState() : _x(0), _y(0), _zoom(1)
        {
        }

        CameraState(double x, double y, double zoom) : _x(x), _y(y), _zoom(zoom)
        {
        }
    };

    CameraState lerp(const CameraState from, const CameraState to, double t)
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
        double _speed = 1;
        CameraState _current = {};
        CameraState _target = {};

    public:
        void speed(double speed) { _speed = speed; }

        CameraState current() { return _current; }

        CameraState target() { return _target; }

        Camera() {}

        ~Camera() {}

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
} // namespace core::render
