#include <imgui.h>
#include <raylib.h>

#include "components/Acceleration.h"
#include "components/Velocity.h"
#include "debug/FPSCounter.h"
#include "debug/Profiler.h"
#include "game/GameLoop.h"
#include "glue/Glue.h"
#include "systems/DebugRender.h"
#include "systems/Input.h"
#include "systems/Physic.h"
#include "systems/TerrainRender.h"
#include "world/World.h"

using namespace components;

int main()
{
    glue::initialize();

    world::World world{256, 256};

    world.register_system<systems::Input>();
    world.register_system<systems::DebugRender>();
    world.register_system<systems::Physic>();
    world.register_system<systems::TerrainRender>();

    world.create_entity()
        .with<Position>(64.0f, 64.0f, 0.0f)
        .with<Acceleration>()
        .with<Velocity>()
        .with<Player>();

    game::GameLoop loop{world};

    loop.run();

    glue::uninitialize();

    return 0;
}