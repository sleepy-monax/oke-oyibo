#pragma once

#include "core/Scene.h"
#include "core/Texture.h"
#include "core/Camera.h"
#include "core/World.h"

namespace game
{
    class EndGameScene : public core::Scene
    {
        private: 
            core::Camera _camera;
            utils::RefPtr<core::World> _world;
            double _accumulator = 4;

        public:
            EndGameScene(core::Director &dir, core::Registry &reg);
            ~EndGameScene();

            void render() override;

            void on_switch_in() override;

            void on_switch_out() override;

            bool stackFrame(core::Time &time);
    };
} // namespace game
