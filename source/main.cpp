#include <imgui.h>
#include <raylib.h>

#include "components/Acceleration.h"
#include "components/Velocity.h"
#include "debug/FPSCounter.h"
#include "debug/Profiler.h"
#include "glue/Glue.h"
#include "loop/GameLoop.h"
#include "systems/DebugRender.h"
#include "systems/Input.h"
#include "systems/Physic.h"
#include "world/World.h"

using namespace components;

int main()
{
    glue::initialize();

    world::World world{};

    world.register_system<systems::Input>();
    world.register_system<systems::DebugRender>();
    world.register_system<systems::Physic>();

    world.create_entity()
        .with<Position>(64.0, 64.0, 0.0)
        .with<Acceleration>()
        .with<Velocity>()
        .with<Player>();

    loop::GameLoop loop{world};

    loop.run();

    glue::uninitialize();

    return 0;
}