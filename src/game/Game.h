#pragma once

#include <raylib.h>

#include "core/RenderContext.h"
#include "core/UpdateContext.h"
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
        core::RenderContext _render_context{};

    public:
        Game(core::World &world)
            : _world(world)
        {
        }

        ~Game() {}

        void run()
        {
            _render_context.resize_to_fit_the_screen();

            update();

            render();
        }

        void update()
        {
            core::UpdateContext context{GetFrameTime(), GetTime()};
            _world.update(context);
        }

        void render()
        {
            _render_context.clear();
            _world.render(_render_context);
            _render_context.compose();

            Rectangle rect{0, 0, _render_context.width() * 1.0f, _render_context.height() * 1.0f};
            DrawTexturePro(_render_context.composite().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
        }
    };
} // namespace game