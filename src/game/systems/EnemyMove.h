#pragma once

#include "core/System.h"
#include "utils/Random.h"

namespace game
{
    class EnemyMove: public core::System
    {
        double _accumulator = 1;
        utils::Random _random{};

        void update(core::World &world, core::Time &time) override;
    };
} // namespace game
