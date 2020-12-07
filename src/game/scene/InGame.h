#pragma once

#include <imgui.h>
#include <raylib.h>

#include "core/Director.h"
#include "core/Registry.h"
#include "core/Scene.h"
#include "core/Time.h"
#include "editor/Editor.h"
#include "game/Game.h"

#include "utils/OwnPtr.h"

namespace game
{
    class InGame: public core::Scene
    {
    private:
        bool _debugging = false;
        utils::OwnPtr<game::Game> _game;
        utils::OwnPtr<editor::Editor> _editor;
        utils::RefPtr<core::World> _world;

    public:
        InGame(core::Director &dir, core::Registry &reg);
        ~InGame() override;

        void update(core::Time &time) override;
        void render() override;
        void on_switch_in() override;
        void on_switch_out() override;
    };

} // namespace game
