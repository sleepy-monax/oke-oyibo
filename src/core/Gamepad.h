#pragma once

#include <raylib.h>

#include "core/Controller.h"

namespace core
{
    class GamePad: public Controller
    {
    private:
    public:
        GamePad() {}

        bool down(Control control) override
        {
            switch (control)
            {
            case Control::MOVE_UP:
                return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.5;

            case Control::MOVE_DOWN:
                return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.5;

            case Control::MOVE_LEFT:
                return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.5;

            case Control::MOVE_RIGHT:
                return GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.5;

            case Control::ACTION_MAIN:
                return IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

            case Control::ACTION_SECONDARY:
                return IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

            case Control::ZOOM_IN:
                return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);

            case Control::ZOOM_OUT:
                return IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);

            case Control::MENU_OPEN:
                return IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_UP);

            default:
                return false;
            }
        }

        bool pressed(Control control) override
        {
            switch (control)
            {
            case Control::MOVE_UP:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP);

            case Control::MOVE_DOWN:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);

            case Control::MOVE_LEFT:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);

            case Control::MOVE_RIGHT:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);

            case Control::ACTION_MAIN:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

            case Control::ACTION_SECONDARY:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

            case Control::ACTION_NEXT_ITEM:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

            case Control::ZOOM_IN:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP);

            case Control::ZOOM_OUT:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);

            case Control::MENU_OPEN:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP);

            case Control::MENU_PREV:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);

            case Control::MENU_NEXT:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);

            case Control::MENU_ACTION:
                return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

            default:
                return false;
            }
        }
    };
} // namespace core