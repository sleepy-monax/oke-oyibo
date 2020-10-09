#pragma once

#include <raylib.h>

#include "core/input/Controller.h"

namespace core::input
{
    class Keyboard : public Controller
    {
    private:
    public:
        Keyboard() {}

        bool pressed(Control control) override
        {
            switch (control)
            {
            case Control::MOVE_UP:
                return IsKeyDown(KEY_Z);
            case Control::MOVE_DOWN:
                return IsKeyDown(KEY_S);
            case Control::MOVE_LEFT:
                return IsKeyDown(KEY_Q);
            case Control::MOVE_RIGHT:
                return IsKeyDown(KEY_D);
            case Control::ACTION_MAIN:
                return IsKeyDown(KEY_J);
            case Control::ACTION_SECONDARY:
                return IsKeyDown(KEY_K);
            default:
                return false;
            }
        }
    };
} // namespace core::input