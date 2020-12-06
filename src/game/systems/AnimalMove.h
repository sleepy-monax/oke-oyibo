#pragma once

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class AnimalMove : public core::System
    {
    private:
        double _accumulator = 1;
        utils::Random _random{};

    public:

        void update(core::World &world, core::Time &time) override;
    };
    
} // namespace game
