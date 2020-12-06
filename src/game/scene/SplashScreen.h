#pragma once

#include <raylib.h>

#include "core/glue/Glue.h"

#include "core/Director.h"
#include "core/Graphics.h"
#include "core/Scene.h"
#include "core/Scheduler.h"

#include "game/scene/CreateGame.h"

namespace game
{

    class SplashScreen: public core::Scene
    {
    private:
        core::Scheduler _scheduler{};
        core::Texture _logo;

    public:
        SplashScreen(core::Director &dir, core::Registry &reg) :
            core::Scene(dir, reg)
        {
            _logo = reg.texture("logo");

            _scheduler.schedule(3, [&]() {
                dir.switch_scene<CreateGame>();
            });
        }

        void update(core::Time &time) override
        {
            _scheduler.update(time);
        }

        void render() override
        {
            ClearBackground(WHITE);

            core::draw_texture(_logo, _logo.bound().centered_within(core::glue::screen()), WHITE);
        }
    };

} // namespace game
