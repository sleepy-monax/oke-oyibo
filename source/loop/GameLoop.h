#pragma once

#include <raylib.h>

#include "debug/FPSCounter.h"
#include "debug/Profiler.h"
#include "glue/Glue.h"
#include "loop/RenderContext.h"
#include "loop/UpdateContext.h"
#include "world/World.h"

namespace loop
{
    class GameLoop
    {
    private:
        world::World &_world;

        debug::FPSCounter fps_counter{};

        debug::Profiler frame_time_profiler{"Frame Time"};
        debug::Profiler update_profiler{"Update"};
        debug::Profiler render_profiler{"Render"};
        debug::Profiler display_profiler{"Display"};

    public:
        GameLoop(world::World &world)
            : _world(world)
        {
        }

        ~GameLoop() {}

        void run()
        {
            while (!glue::should_exit())
            {
                glue::begin_frame();

                frame_time_profiler.mesure([&]() {
                    update_profiler.mesure([&]() {
                        UpdateContext context{GetFrameTime(), GetTime()};
                        _world.update(context);
                    });

                    render_profiler.mesure([&]() {
                        RenderContext context{};
                        _world.render(context);
                    });

                    display_profiler.mesure([&]() {
                        ImGui::Begin("Profiler");
                        fps_counter.mesure_and_display();
                        frame_time_profiler.display();
                        update_profiler.display();
                        render_profiler.display();
                        display_profiler.display();
                        ImGui::End();

                        _world.display();
                    });
                });

                glue::end_frame();
            }
        }
    };
} // namespace loop
