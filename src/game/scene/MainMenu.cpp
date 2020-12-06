#include "MainMenu.h"
#include "imgui.h"
#include "core/Director.h"
#include "game/scene/CreateGame.h"
#include "core/Graphics.h"

namespace game
{
    MainMenu::MainMenu(core::Director &dir, core::Registry &reg):
        core::Scene(dir, reg) 
    {
        //Charge image for background
        background_image =  reg.texture("background");
    }

    MainMenu::~MainMenu()
    {
    }

    void MainMenu::update(core::Time &time)
    {
        Scene::update(time);
    }

    void MainMenu::render()
    {
        //Put image on indow background
        core::draw_texture(background_image, core::glue::screen(),  WHITE);

        //Create menu window
        ImGui::Begin("Main menu");

        //Set size of the menu and position
        ImVec2 vector(250, 200), button_size(200,30);
        ImGui::SetWindowSize(vector);
        ImGui::SetCursorPosX(50.);
        ImGui::Text("Welcome to Oke Oyibo");
        ImGui::SetCursorPosX(25.);

        //Button for launch the game
        if (ImGui::Button("Create game", button_size))
        {
            director().switch_scene<game::CreateGame>();
        }
        
        //Other buttons
        //Load a save
        ImGui::SetCursorPosX(25.);
        ImGui::Button("Load game", button_size);
        //Change settings
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