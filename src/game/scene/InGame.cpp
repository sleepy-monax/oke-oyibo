#include "game/scene/InGame.h"

#include "core/Keyboard.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

#include "base/components/CastShadow.h"
#include "base/components/LightSource.h"
#include "base/components/Player.h"
#include "base/components/Sprite.h"
#include "game/components/Breakable.h"
#include "game/components/HoldItem.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"
#include "game/components/Pickable.h"
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

        auto world_center = world->terrain().bound().center();

        world->create_entity()
            .with<base::Position>(world_center.x(), world_center.y(), 0.0f)
            .with<base::Acceleration>()
            .with<base::Velocity>()
            .with<base::LightSource>(128.0f, WHITE)
            .with<game::Health>(10, 10)
            .with<game::Hunger>(20.0f, 20.0f)
            .with<game::Thirst>(20.0f, 20.0f)
            .with<base::Player>(0)
            .with<base::Sprite>(registry().texture("character"))
            .with<game::Stamina>(20.0f, 20.0f)
            .with<game::Inventory>()
            .with<base::CastShadow>(4, utils::Vec2f{0.5, 0})
            .with<game::HoldItem>();

        Stack table(Item("table", core::Texture()), 12);
        world->create_entity()
            .with<game::Pickable>(table)
            .with<base::Position>(60.0f, 60.0f, 0.0f)
            .with<base::LightSource>(50.0f, WHITE)
            .with<base::Sprite>(registry().texture("table"));

        Stack tree(Item("log", core::Texture()), 12);
        world->create_entity()
            .with<game::Breakable>(tree, 5)
            .with<base::Position>(50.0f, 60.0f, 0.0f)
            .with<base::LightSource>(50.0f, WHITE)
            .with<base::Sprite>(registry().texture("tree"));

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
