#pragma once

#include <raylib.h>

#include "core/Scene.h"
#include "core/Scheduler.h"

namespace game
{

    class SplashScreen: public core::Scene
    {
    private:
        core::Scheduler _scheduler{};

    public:
        SplashScreen()
        {
            _scheduler.schedule(3, []() {

            });
        }

        void update(core::Time &time) override
        {
            _scheduler.update(time);
        }

        void render() override
        {
            ClearBackground(BLACK);
        }
    };

} // namespace game
