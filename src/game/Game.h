#pragma once

#include <raylib.h>

#include "core/Camera.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"

#include "base/components/Position.h"

namespace game
{
    class Game
    {
    private:
        utils::RefPtr<core::World> _world;

    public:
        Game(utils::RefPtr<core::World> world) :
            _world(world)
        {
        }

        ~Game() {}

        void update(core::Time &time)
        {
            for (size_t i = 0; i < _world->players().count(); i++)
            {
                _world->players()[i].camera().resize_to_fit_the_screen();
            }

            _world->update(time);
        }

        void render()
        {
            for (size_t i = 0; i < _world->players().count(); i++)
            {
                auto &camera = _world->players()[i].camera();

                camera.clear();
                _world->render(camera);
                camera.compose();
            }

            compose();
        }

        void compose()
        {
            for (size_t i = 0; i < _world->players().count(); i++)
            {
                auto &cam = _world->players()[i].camera();

                Rectangle rect{0, 0, cam.width() * 1.0f, cam.height() * 1.0f};
                DrawTexturePro(cam.composite().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            }
        }
    };
} // namespace game