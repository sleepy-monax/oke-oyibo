#pragma once

#include <raylib.h>

#include "core/debug/FPSCounter.h"
#include "core/debug/Inspector.h"
#include "core/debug/Profiler.h"
#include "core/game/RenderContext.h"
#include "core/game/UpdateContext.h"
#include "core/glue/Glue.h"
#include "core/world/World.h"

#include "core/components/Acceleration.h"
#include "core/components/Position.h"
#include "core/components/Velocity.h"

namespace game
{
    class Game
    {
    private:
        core::world::World &_world;
        core::game::RenderContext _render_context{};

    public:
        Game(core::world::World &world)
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
            core::game::UpdateContext context{GetFrameTime(), GetTime()};
            _world.update(context);
        }

        void render()
        {
            _world.render(_render_context);

            _render_context.composite().use_and_do([&]() {
                Rectangle rect{0, 0, _render_context.width() * 1.0f, _render_context.height() * 1.0f};
                DrawTexturePro(_render_context.terrain().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(_render_context.shadows().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(_render_context.entities().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(_render_context.light().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
                DrawTexturePro(_render_context.overlay().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);
            });
        }
    };
} // namespace game