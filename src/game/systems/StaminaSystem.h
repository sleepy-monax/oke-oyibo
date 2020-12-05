#pragma once

#include <base/components/Acceleration.h>
#include <game/components/Stamina.h>

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

#include "core/Registry.h"
#include "core/Scene.h"

namespace game {
    class StaminaSystem : public core::System
    {
        private:
            double _accumulator = 0;
            double _accumAccel = 0;
            core::Texture staminaTexture;

        public:
            StaminaSystem();

            void update(core::World &world, core::Time &time);

            bool stackFrame(core::Time &time);

            bool stackFrameForAcc(core::Time &time);

            void on_load(core::Registry &registry) override;

            void render(core::World &world, core::Camera &camera);
    };
}
