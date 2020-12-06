#pragma once

#include "core/Scene.h"
#include "core/Texture.h"
#include "core/Camera.h"
#include "core/World.h"

namespace game
{
    class CreateGame : public core::Scene
    {
    private:
        core::Texture background_image;
        core::Camera _camera;
        utils::RefPtr<core::World> _world;
        double _accumulator = 15;

    public:
        CreateGame(core::Director &dir, core::Registry &reg);
        ~CreateGame();

        void update(core::Time &time) override;

        void render() override;

        void on_switch_in() override;

        void on_switch_out() override;

        bool stackFrame(core::Time &time);
    };
    
} // namespace game
