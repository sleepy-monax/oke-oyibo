#pragma once

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class DrinkSystem : public core::System
    {
    private:
        /* data */
    public:
        DrinkSystem(/* args */);
        ~DrinkSystem();

        void update(core::World &world, core::Time &time);
    };

} // namespace game
