#pragma once

#include <raylib.h>

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "core/System.h"
#include "core/World.h"

#include "game/components/Health.h"

namespace game
{
    class HealthBar: public core::System
    {
    private:

    public:
        HealthBar();

        void update(core::World &world, core::Time &time) override;
        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace game
