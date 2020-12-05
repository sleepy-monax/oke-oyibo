#pragma once

#include "core/System.h"
#include "core/Registry.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class AttackSystem : public core::System
    {
        private:
            double _accumulator = 0;
        public:
            AttackSystem();
            ~AttackSystem();

            void update(core::World &world, core::Time &time);
            bool stackFrame(core::Time &time);

            friend void inspect<game::AttackSystem>(game::AttackSystem &attackSystem);
    };
}

