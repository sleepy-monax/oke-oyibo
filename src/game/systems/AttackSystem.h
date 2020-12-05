#pragma once

#include "core/Registry.h"
#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class AttackSystem: public core::System
    {
        double _accumulator = 0;

        void update(core::World &world, core::Time &time);
        bool stackFrame(core::Time &time);
        friend void inspect<game::AttackSystem>(game::AttackSystem &attackSystem);
    };
} // namespace game
