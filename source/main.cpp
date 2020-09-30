#include <imgui.h>
#include <raylib.h>

#include "debug/FPSCounter.h"
#include "debug/Profiler.h"
#include "glue/Glue.h"
#include "systems/Input.h"
#include "world/World.h"

int main(void)
{
    glue::initialize();

    debug::FPSCounter fps_counter{};

    debug::Profiler update_profiler{"Update"};
    debug::Profiler render_profiler{"Render"};
    debug::Profiler display_profiler{"Display"};

    world::World world{};

    world.register_system<systems::System>("Test");
    world.register_system<systems::Input>();

    while (!glue::should_exit())
    {
        glue::begin_frame();
        fps_counter.mesure_and_display();

        update_profiler.mesure([&]() {
            world.update();
        });

        render_profiler.mesure([&]() {
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            world.render();
        });

        display_profiler.mesure([&]() {
            world.display();
        });

        ImGui::Begin("Profiler");

        if (ImGui::CollapsingHeader("Game Loop"))
        {
            update_profiler.display();
            render_profiler.display();
            display_profiler.display();
        }
        ImGui::End();

        glue::end_frame();
    }

    glue::uninitialize();

    return 0;
}