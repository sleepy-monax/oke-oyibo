#pragma once

#include <utils/Vec.h>

namespace base
{
    struct Move
    {
        bool moving = false;
        utils::Vec2f destination{};
        double speed;

        void move_to(utils::Vec2f dest)
        {
            destination = dest;
            moving = true;
        }

        void stop()
        {
            destination = {0, 0};
            moving = false;
        }

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
