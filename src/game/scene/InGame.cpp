#include "game/scene/InGame.h"

#include "core/Keyboard.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "game/generator/Generator.h"
#include "game/scene/CreateGame.h"
#include "game/scene/EndGameScene.h"

namespace game
{

    InGame::InGame(core::Director &dir, core::Registry &reg, utils::RefPtr<core::World> world) :
        core::Scene(dir, reg), _world(world)
    {
        _editor = utils::own<editor::Editor>(_world);
        _editor->open<editor::Entities>();
        _editor->open<editor::Inspector>();
        _editor->open<editor::Profiler>();
        _editor->open<editor::Systems>();
        _editor->open<editor::Viewport>();

        _game = utils::own<game::Game>(_world);
    }

    InGame::~InGame()
    {
    }

    void InGame::on_switch_in()
    {
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

        if (IsKeyPressed(KEY_ESCAPE))
        {
            director().switch_scene<game::CreateGame>();
        }

        if (_debugging)
        {
            _editor->update(time);
        }
        else
        {
            _game->update(time);
        }
        if (_world->isWin())
        {
            director().switch_scene<game::EndGameScene>();
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
