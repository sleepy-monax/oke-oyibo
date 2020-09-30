#include <imgui.h>
#include <raylib.h>

#include "debug/FPSCounter.h"
#include "debug/Profiler.h"
#include "glue/Glue.h"
#include "loop/GameLoop.h"
#include "systems/DebugRender.h"
#include "systems/Input.h"
#include "world/World.h"

int main(void)
{
    glue::initialize();

    world::World world{};

    world.register_system<systems::Input>();
    world.register_system<systems::DebugRender>();

    loop::GameLoop loop{world};

    loop.run();

    glue::uninitialize();

    return 0;
}