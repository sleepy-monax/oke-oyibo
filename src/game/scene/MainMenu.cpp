//
// Created by oslo on 11/23/20.
//

#include "MainMenu.h"

namespace game
{
    MainMenu::MainMenu() {}

    MainMenu::~MainMenu() {

    }

    void MainMenu::update(core::Time &time) {
        Scene::update(time);
    }

    void MainMenu::render() {
        Scene::render();
    }

    void MainMenu::on_switch_in() {
        Scene::on_switch_in();
    }

    void MainMenu::on_switch_out() {
        Scene::on_switch_out();
    }
}
