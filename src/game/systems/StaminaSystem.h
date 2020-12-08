#pragma once

#include "core/System.h"

namespace game
{
    class StaminaSystem: public core::System
    {
        double _accumulator = 0;
        double _accumAccel = 0;
        core::Texture staminaTexture;

        void update(core::World &world, core::Time &time);

        bool stackFrame(core::Time &time);

        void on_load(core::Registry &registry) override;

        void render(core::World &world, core::Camera &camera);
    };

} // namespace game
