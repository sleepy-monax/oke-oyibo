#include <imgui.h>
#include <raylib.h>

#include "base/components/Acceleration.h"
#include "base/components/LightSource.h"
#include "base/components/Velocity.h"
#include "base/systems/Camera.h"
#include "base/systems/DebugRender.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Physic.h"
#include "base/systems/TerrainRender.h"
#include "core/World.h"
#include "core/glue/Glue.h"
#include "core/input/Keyboard.h"

#include "core/Registry.h"
#include "editor/Editor.h"
#include "editor/EntityList.h"
#include "editor/SystemList.h"
#include "game/Game.h"

using namespace base;

int main()
{
    bool debugging = false;

    core::glue::initialize();

    core::Registry registry{};

    registry.register_system<Input>("input");
    registry.register_system<DebugRender>("debug");
    registry.register_system<Physic>("physic");
    registry.register_system<TerrainRender>("terrain");
    registry.register_system<base::Light>("light");
    registry.register_system<base::Camera>("camera");

    registry.register_component<Acceleration>("acceleration");
    registry.register_component<Player>("player");
    registry.register_component<Position>("position");
    registry.register_component<Velocity>("velocity");
    registry.register_component<LightSource>("light-source");

    core::World world{registry, 256, 256};

    world.add_player({"bob", utils::own<core::input::Keyboard>()});
    world.players()[0].camera().zoom_in();

    world.create_entity()
        .with<Position>(64.0f, 64.0f, 0.0f)
        .with<Acceleration>()
        .with<Velocity>()
        .with<LightSource>(128.0f, WHITE)
        .with<Player>(0);

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