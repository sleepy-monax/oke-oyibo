#include "game/scene/InGame.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "base/components/Acceleration.h"
#include "base/components/LightSource.h"
#include "base/components/Velocity.h"
#include "base/systems/Camera.h"
#include "base/systems/DebugRender.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Physic.h"
#include "base/systems/TerrainRender.h"
#include "game/systems/HealthBar.h"
#include "game/systems/HungerSystem.h"
#include "game/systems/ThirstSystem.h"

namespace game
{

    InGame::InGame()
    {
        auto registry = utils::make<core::Registry>();

        registry->register_system<base::Input>("input");
        registry->register_system<base::DebugRender>("debug");
        registry->register_system<base::Physic>("physic");
        registry->register_system<base::TerrainRender>("terrain");
        registry->register_system<base::Light>("light");
        registry->register_system<base::Camera>("camera");
        registry->register_system<game::HealthBar>("health-bar");
        registry->register_system<game::HungerSystem>("hunger");
        registry->register_system<game::ThirstSystem>("thirst");

        registry->register_component<base::Player>("player");
        registry->register_component<base::Position>("position");
        registry->register_component<base::Velocity>("velocity");
        registry->register_component<base::Acceleration>("acceleration");
        registry->register_component<base::LightSource>("light-source");
        registry->register_component<game::Health>("health");
        registry->register_component<game::Hunger>("hunger");
        registry->register_component<game::Thirst>("thirst");

        auto world = utils::make<core::World>(registry, 256, 256);

        world->add_player({"bob", utils::own<core::Keyboard>()});
        world->players()[0].camera().zoom_in();
        world->players()[0].camera().speed(10);

        world->create_entity()
            .with<base::Position>(64.0f, 64.0f, 0.0f)
            .with<base::Acceleration>()
            .with<base::Velocity>()
            .with<base::LightSource>(128.0f, WHITE)
            .with<game::Health>(10)
            .with<game::Hunger>(10.0f, 10.0f)
            .with<game::Thirst>(20.0f, 20.0f)
            .with<base::Player>(0);

        _editor = utils::own<editor::Editor>(world);
        _editor->open<editor::Entities>();
        _editor->open<editor::Inspector>();
        _editor->open<editor::Profiler>();
        _editor->open<editor::Systems>();
        _editor->open<editor::Viewport>();

        _game = utils::own<game::Game>(world);
    }
    InGame::~InGame()
    {
    }

    void InGame::update(core::Time &time)
    {
        if (IsKeyPressed(KEY_F3))
        {
            _debugging = !_debugging;
        }

        if (_debugging)
        {
            _editor->update(time);
        }
        else
        {
            _game->update(time);
        }
    }

    void InGame::render()
    {
        if (_debugging)
        {
            _editor->render();
            _editor->display();
        }
        else
        {
            _game->render();
        }
    }

    void InGame::on_switch_in()
    {
    }

    void InGame::on_switch_out()
    {
    }

} // namespace game
