#include <imgui.h>
#include <raylib.h>

#include "core/components/Acceleration.h"
#include "core/components/Velocity.h"
#include "core/debug/FPSCounter.h"
#include "core/debug/Profiler.h"
#include "core/game/GameLoop.h"
#include "core/glue/Glue.h"
#include "core/systems/DebugRender.h"
#include "core/systems/Input.h"
#include "core/systems/Physic.h"
#include "core/systems/TerrainRender.h"
#include "core/world/World.h"

using namespace core::components;

int main()
{
    core::glue::initialize();

    core::world::World world{256, 256};

    world.register_system<core::systems::Input>();
    world.register_system<core::systems::DebugRender>();
    world.register_system<core::systems::Physic>();
    world.register_system<core::systems::TerrainRender>();

    world.create_entity()
        .with<Position>(64.0f, 64.0f, 0.0f)
        .with<Acceleration>()
        .with<Velocity>()
        .with<Player>();

    core::game::GameLoop loop{world};

    loop.run();

    core::glue::uninitialize();

    return 0;
}