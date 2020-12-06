#pragma once

#include <raylib.h>

#include "core/Controller.h"

namespace core
{
    class Keyboard: public Controller
    {
    private:
    public:
        Keyboard() {}

        bool down(Control control) override
        {
            switch (control)
            {
            case Control::MOVE_UP:
                return IsKeyDown(KEY_W);

            case Control::MOVE_DOWN:
                return IsKeyDown(KEY_S);

            case Control::MOVE_LEFT:
                return IsKeyDown(KEY_A);

            case Control::MOVE_RIGHT:
                return IsKeyDown(KEY_D);

            case Control::ACTION_MAIN:
                return IsKeyDown(KEY_J);

            case Control::ACTION_SECONDARY:
                return IsKeyDown(KEY_K);

            case Control::ZOOM_IN:
                return IsKeyDown(KEY_PAGE_UP);

            case Control::ZOOM_OUT:
                return IsKeyDown(KEY_PAGE_DOWN);

            case Control::OPEN_MENU:
                return IsKeyDown(KEY_E);

            default:
                return false;
            }
        }

        bool pressed(Control control) override
        {
            switch (control)
            {
            case Control::MOVE_UP:
                return IsKeyPressed(KEY_W);

            case Control::MOVE_DOWN:
                return IsKeyPressed(KEY_S);

            case Control::MOVE_LEFT:
                return IsKeyPressed(KEY_A);

            case Control::MOVE_RIGHT:
                return IsKeyPressed(KEY_D);

            case Control::ACTION_MAIN:
                return IsKeyPressed(KEY_J);

            case Control::ACTION_SECONDARY:
                return IsKeyPressed(KEY_K);

            case Control::ZOOM_IN:
                return IsKeyPressed(KEY_PAGE_UP);

            case Control::ZOOM_OUT:
                return IsKeyPressed(KEY_PAGE_DOWN);

            case Control::OPEN_MENU:
                return IsKeyDown(KEY_E);

            default:
                return false;
            }
        }
    };
} // namespace core