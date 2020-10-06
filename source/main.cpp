#include <imgui.h>
#include <raylib.h>

#include "base/components/Acceleration.h"
#include "base/components/LightSource.h"
#include "base/components/Velocity.h"
#include "base/systems/DebugRender.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Physic.h"
#include "base/systems/TerrainRender.h"
#include "core/World.h"
#include "core/glue/Glue.h"

#include "core/Registry.h"
#include "editor/Editor.h"
#include "editor/EntityList.h"
#include "editor/SystemList.h"
#include "game/Game.h"

using namespace base;
using namespace base;

int main()
{
    bool debugging = false;

    core::glue::initialize();

    core::Registry registry{};

    registry.register_system<Input>("Input");
    registry.register_system<DebugRender>("DebugRender");
    registry.register_system<Physic>("Physic");
    registry.register_system<TerrainRender>("TerrainRender");

    registry.register_component<Acceleration>("Acceleration");
    registry.register_component<Player>("Player");
    registry.register_component<Position>("Position");
    registry.register_component<Velocity>("Velocity");
    registry.register_component<LightSource>("LightSource");

    core::World world{registry, 256, 256};

    world.register_system<Input>();
    world.register_system<DebugRender>();
    world.register_system<Physic>();
    world.register_system<TerrainRender>();
    world.register_system<Light>();

    world.create_entity()
        .with<Position>(64.0f, 64.0f, 0.0f)
        .with<Acceleration>()
        .with<Velocity>()
        .with<LightSource>(16.0f, WHITE)
        .with<Player>();

    editor::Editor editor{world};
    editor.open<editor::EntityList>();
    editor.open<editor::SystemList>();

    game::Game game{world};

    while (!core::glue::should_exit())
    {
        if (IsKeyPressed(KEY_F3))
        {
            debugging = !debugging;
        }

        core::glue::begin_frame();

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