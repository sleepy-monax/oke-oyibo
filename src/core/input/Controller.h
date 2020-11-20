#pragma once

#include "utils/Macros.h"

namespace core::input
{

    enum class Control
    {
        NONE,

        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        ACTION_MAIN,
        ACTION_SECONDARY,
    };

    class Controller
    {
    private:
    public:
        Controller() {}

        virtual ~Controller() {}

        virtual bool pressed(Control control)
        {
            __unused(control);

            return false;
        }
    };

} // namespace core::input
