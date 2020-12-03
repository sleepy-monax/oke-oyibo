#pragma once

#include "core/System.h"
#include "core/World.h"

#include "game/components/Health.h"
#include "game/components/Hunger.h"
#include "game/components/Thirst.h"

namespace game
{
    class RegenSystem : public core::System
    {
        private:
            double _accumulator = 0;
        public:
            RegenSystem();

            void update(core::World &world, core::Time &time);

            bool stackFrame(core::Time &time);
    };
}