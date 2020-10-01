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

namespace core::game
{
    class GameLoop
    {
    private:
        bool _debugging = true;

        world::World &_world;
        RenderContext _render_context{};

        debug::FPSCounter fps_counter{};

        debug::Profiler frame_time_profiler{"Frame Time"};
        debug::Profiler update_profiler{"Update"};
        debug::Profiler render_profiler{"Render"};
        debug::Profiler display_profiler{"Display"};

        entt::entity _inspector_selected;
        MM::EntityEditor<entt::entity> _inspector{};

    public:
        GameLoop(world::World &world)
            : _world(world)
        {
            _inspector.registerComponent<components::Velocity>("Velocity");
            _inspector.registerComponent<components::Position>("Position");
            _inspector.registerComponent<components::Acceleration>("Acceleration");
        }

        ~GameLoop() {}

        void run()
        {
            while (!glue::should_exit())
            {
                if (IsKeyPressed(KEY_F3))
                {
                    _debugging = !_debugging;
                }

                glue::begin_frame();
                debug::Profiler::new_frame();

                frame_time_profiler.mesure([&]() {
                    update_profiler.mesure([&]() {
                        update();
                    });

                    render_profiler.mesure([&]() {
                        if (!_debugging)
                        {
                            _render_context.resize_to_fit_the_screen();
                        }

                        render();
                    });

                    display_profiler.mesure([&]() {
                        if (_debugging)
                        {
                            display();
                        }
                    });
                });

                glue::end_frame();
            }
        }

        void update()
        {
            UpdateContext context{GetFrameTime(), GetTime()};
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

        void display()
        {
            ImGui::DockSpaceOverViewport();

            ImGui::Begin("Viewport");

            ImGui::GetWindowSize();
            //_render_context.resize_to_fit(size.x, size.y);
            _render_context.composite().display(1);

            ImGui::End();

            ImGui::Begin("Profiler");
            fps_counter.mesure_and_display();
            frame_time_profiler.display();
            update_profiler.display();
            render_profiler.display();
            display_profiler.display();
            ImGui::End();

            _inspector.renderSimpleCombo(_world.entities(), _inspector_selected);
            _render_context.display();
            _world.display();
        }
    };
} // namespace core::game
