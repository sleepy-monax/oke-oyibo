#pragma once

#include "game/components/Breakable.h"

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class BreakableSystem : public core::System
    {
    private:
        /* data */
    public:
        BreakableSystem(/* args */);
        ~BreakableSystem();

        void update(core::World &world, core::Time &time);
    };

} // namespace game
