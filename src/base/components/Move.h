#pragma once

#include <utils/Vec.h>

namespace base
{
    struct Move
    {
        bool moving = false;
        utils::Vec2f destination{};

        double speed;

        Move()
        {
            speed = 0.1;
        }

        Move(double speed)
        {
            this->speed = speed;
        }
    };
} // namespace base
