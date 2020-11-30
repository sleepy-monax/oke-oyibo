#pragma once

#include "core/Scene.h"

namespace game
{
    class CreateGame : public core::Scene
    {
    private:
    public:
        CreateGame(core::Director &dir, core::Registry &reg);
        ~CreateGame();

        void update(core::Time &time) override;

        void render() override;

        void on_switch_in() override;

        void on_switch_out() override;
    };
    
} // namespace game
