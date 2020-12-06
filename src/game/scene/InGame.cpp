#include "game/scene/InGame.h"

#include "core/Keyboard.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "base/components/CastShadow.h"
#include "base/components/Colider.h"
#include "base/components/LightSource.h"
#include "base/components/Momentum.h"
#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/components/Sprite.h"
#include "game/components/Attack.h"
#include "game/components/Breakable.h"
#include "game/components/Enemy.h"
#include "game/components/HoldItem.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"
#include "game/components/Pickable.h"
#include "game/components/Prey.h"
#include "game/components/Stamina.h"
#include "game/components/Thirst.h"
#include "game/inventory/Item.h"
#include "game/inventory/Stack.h"

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

        game::Stack stack(game::Item("sword", registry().texture("sword")), 1);
        world->create_entity()
            .with<game::Pickable>(stack)
            .with<base::Position>(2060.0f, 2060.0f, 0.0f)
            .with<base::Sprite>(registry().texture("sword"));

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
