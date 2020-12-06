#include "game/scene/InGame.h"

#include "core/Keyboard.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "game/generator/Generator.h"

namespace game
{

    InGame::InGame(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg)
    {
    }

    InGame::~InGame()
    {
    }

    void InGame::on_switch_in()
    {
        Generator gen{};

        auto world = gen.generate(registry(), time(nullptr));

        world->add_player({"bob", utils::own<core::Keyboard>()});
        world->players()[0].camera().zoom_in();
        world->players()[0].camera().speed(10);
        world->players()[0].camera().jump_to(world->terrain().bound().center());

        world->create_entity(registry().blueprint("player"), world->terrain().bound().center());

        _editor = utils::own<editor::Editor>(world);
        _editor->open<editor::Entities>();
        _editor->open<editor::Inspector>();
        _editor->open<editor::Profiler>();
        _editor->open<editor::Systems>();
        _editor->open<editor::Viewport>();

        _game = utils::own<game::Game>(world);
    }

    void InGame::on_switch_out()
    {
    }

    void InGame::update(core::Time &time)
    {
        if (IsKeyPressed(KEY_F3))
        {
            _debugging = !_debugging;
        }

        if (IsKeyPressed(KEY_R))
        {
            on_switch_in();
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

} // namespace game
