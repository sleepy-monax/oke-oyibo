//
// Created by oslo on 11/23/20.
//

#include "MainMenu.h"
#include "imgui.h"
#include "core/Director.h"
#include "game/scene/InGame.h"

namespace game
{
    MainMenu::MainMenu(core::Director &dir, core::Registry &reg):
        core::Scene(dir, reg) {}

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::update(core::Time &time)
    {
        Scene::update(time);
    }

    void MainMenu::render()
    {
        ImGui::Begin("Main menu");

        ImVec2 vector(250, 200), button_size(200,30);
        ImGui::SetWindowSize(vector);
        ImGui::SetCursorPosX(50.);
        ImGui::Text("Welcome to Oke Oyibo");
        ImGui::SetCursorPosX(25.);
        if (ImGui::Button("Create game", button_size))
        {
            director().switch_scene<game::InGame>();
        }
        
        ImGui::SetCursorPosX(25.);
        ImGui::Button("Load game", button_size);
        ImGui::SetCursorPosX(25.);
        ImGui::Button("Settings", button_size);

        ImGui::End();
    }

    void MainMenu::on_switch_in()
    {
        Scene::on_switch_in();
    }

    void MainMenu::on_switch_out()
    {
        Scene::on_switch_out();
    }
} // namespace game
