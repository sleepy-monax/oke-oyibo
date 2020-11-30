//
// Created by oslo on 11/23/20.
//
#pragma once

#include "core/Scene.h"

namespace game
{
    class MainMenu: public core::Scene
    {

    private:
    public:
        MainMenu(core::Director &dir, core::Registry &reg);

        virtual ~MainMenu();

        void update(core::Time &time) override;

        void render() override;

        void on_switch_in() override;

        void on_switch_out() override;
    };
} // namespace game
