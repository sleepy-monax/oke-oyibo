#pragma once

#include <raylib.h>

#include "core/Camera.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"

#include "base/components/Acceleration.h"
#include "base/components/Position.h"
#include "base/components/Velocity.h"

namespace game
{
    class Game
    {
    private:
        core::World &_world;

    public:
        Game(core::World &world)
            : _world(world)
        {
        }

        ~Game() {}

        void run()
        {
            for (size_t i = 0; i < _world.players().count(); i++)
            {
                _world.players()[i].camera().resize_to_fit_the_screen();
            }

            update();

            for (size_t i = 0; i < _world.players().count(); i++)
            {
                render(_world.players()[i].camera());
            }

            compose();
        }

        void update()
        {
            core::Time context{GetFrameTime(), GetTime()};
            _world.update(context);
        }

        void render(core::Camera &context)
        {
            context.clear();
            _world.render(context);
            context.compose();
        }

        void compose()
        {
            for (size_t i = 0; i < _world.players().count(); i++)
            {
                auto &cam = _world.players()[i].camera();

                Rectangle rect{0, 0, cam.width() * 1.0f, cam.height() * 1.0f};
                DrawTexturePro(cam.composite().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            }
        }
    };
} // namespace game