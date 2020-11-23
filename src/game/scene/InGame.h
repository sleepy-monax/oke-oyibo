#pragma once

#include "core/Scene.h"
#include "core/Time.h"
#include "game/Game.h"
#include "editor/Editor.h"


#include <imgui.h>
#include <raylib.h>
#include <src/core/Director.h>

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
#include "game/Game.h"

#include "utils/OwnPtr.h"

namespace game
{
    class InGame : public core::Scene
    {
    private:
        bool _debugging = false;
        utils::OwnPtr<game::Game> _game;
        utils::OwnPtr<editor::Editor> _editor;
    public:
        InGame();
        ~InGame();

        void update(core::Time& time) override;
        void render() override;
        void on_switch_in() override;
        void on_switch_out() override;
    };    
    
} // namespace game