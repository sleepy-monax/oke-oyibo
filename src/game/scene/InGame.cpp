#include "game/scene/InGame.h"
#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

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

        registry->register_component<base::Player>("player");
        registry->register_component<base::Position>("position");
        registry->register_component<base::Velocity>("velocity");
        registry->register_component<base::Acceleration>("acceleration");
        registry->register_component<base::LightSource>("light-source");

        auto world = utils::make<core::World>(registry, 256, 256);

        world->add_player({"bob", utils::own<core::input::Keyboard>()});
        world->players()[0].camera().zoom_in();

        world->create_entity()
            .with<base::Position>(64.0f, 64.0f, 0.0f)
            .with<base::Acceleration>()
            .with<base::Velocity>()
            .with<base::LightSource>(128.0f, WHITE)
            .with<base::Player>(0);

        _editor = utils::own<editor::Editor>(world);
        _editor->open<editor::Entities>();
        _editor->open<editor::Inspector>();
        _editor->open<editor::Profiler>();
        _editor->open<editor::Systems>();
        _editor->open<editor::Viewport>();

        _game = utils::own<game::Game>(world);
    }
    InGame::~InGame() {
    }

    void InGame::update(core::Time &time)
    {
        time.elapsed();
        if (IsKeyPressed(KEY_F3))
        {
            _debugging = !_debugging;
        }

        if (_debugging)
        {
            _editor->run();
        }
        else
        {
            _game->run();
        }
    }

    void InGame::render()
    {
    }

    void InGame::on_switch_in()
    {
    }

    void InGame::on_switch_out()
    {
    }

} // namespace game
