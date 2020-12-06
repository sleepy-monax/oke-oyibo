#pragma once

#include "core/Registry.h"
#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class EatSystem : public core::System
    {
        void update(core::World &world, core::Time &time);
    };
}