#include <imgui.h>

#include "CreateGame.h"
#include "game/scene/InGame.h"
#include "core/Graphics.h"

namespace game
{
    CreateGame::CreateGame(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg) 
    {
        //Charge image for background
        background_image =  reg.texture("background");
    }

    CreateGame::~CreateGame()
    {
    }

    void CreateGame::update(core::Time &time)
    {
        Scene::update(time);
    }

    void CreateGame::render()
    {
        //Put image on indow background
        core::draw_texture(background_image, core::glue::screen(),  WHITE);

        //Create menu window
        ImGui::Begin("Create game");
        ImVec2 vector(720, 480), button_size(200, 30);
        ImGui::SetWindowSize(vector);

        ImGui::Text("%65s", "Welcome to Oke Oyibo ! ");

        //Name of world
        ImGui::Text("%20s", "Name of world : ");
        ImGui::SameLine();
        char buf[64] = "";
        ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

        //Difficulty
        ImGui::Text("%20s", "Difficulty : ");
        ImGui::SameLine();
        static int animate = 1;
        const char *difficulties[] = {"easy", "normal", "hard"};
        ImGui::Combo(" ", &animate, difficulties, IM_ARRAYSIZE(difficulties));

        //Create a game
        ImGui::SetCursorPosX(270.);
        if (ImGui::Button("Create game", button_size))
        {
            director().switch_scene<game::InGame>();
        }

        ImGui::Text("%67s", "Press E to break and collect items");
        ImGui::Text("%78s", "Press F to attack enemies (better with a sword :p)");
        ImGui::Text("%60s", "Go to water to drink");
        ImGui::Text("%73s", "Press A to eat some food if you find some");
        ImGui::Text("%62s", "Try not to be killed");
        ImGui::Text("%67s", "Make a boat to escape the island");
        ImGui::Text("%58s", "Good luck !");
        

        ImGui::End();
    }

    void CreateGame::on_switch_in()
    {
        Scene::on_switch_in();
    }

    void CreateGame::on_switch_out()
    {
        Scene::on_switch_out();
    }
} // namespace game