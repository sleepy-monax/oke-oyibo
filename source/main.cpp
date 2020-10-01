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
#include "editor/Editor.h"
#include "game/Game.h"

using namespace core::components;

int main()
{
    bool debugging = false;

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

    editor::Editor editor{world};

    game::Game game{world};

    while (!core::glue::should_exit())
    {
        if (IsKeyPressed(KEY_F3))
        {
            debugging = !debugging;
        }

        core::glue::begin_frame();
        core::debug::Profiler::new_frame();

        if (debugging)
        {
            editor.run();
        }
        else
        {
            game.run();
        }

        core::glue::end_frame();
    }

    core::glue::uninitialize();

    return 0;
}