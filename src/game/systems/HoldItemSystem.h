#pragma once

#include "core/World.h"
#include "core/Time.h"
#include "core/System.h"

namespace game
{
    class HoldItemSystem : public core::System
    {
    private:

    public:
        HoldItemSystem(/* args */);
        ~HoldItemSystem();

        void update(core::World &world, core::Time &time);
    };

} // namespace game
