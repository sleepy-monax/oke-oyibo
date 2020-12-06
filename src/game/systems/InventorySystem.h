#pragma once

#include "game/components/Inventory.h"

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class InventorySystem: public core::System
    {
        void update(core::World &world, core::Time &time);
    };

} // namespace game
