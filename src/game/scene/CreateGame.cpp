#include <imgui.h>

#include "CreateGame.h"
#include "game/scene/InGame.h"
#include "game/scene/MainMenu.h"

namespace game
{
    CreateGame::CreateGame(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg) {}

    CreateGame::~CreateGame()
    {
    }

    void CreateGame::update(core::Time &time)
    {
        Scene::update(time);
    }

    void CreateGame::render()
    {
        ImGui::Begin("Create game");
        ImVec2 vector(720, 480), button_size(200, 30);
        ImGui::SetWindowSize(vector);

        //Back
        if (ImGui::Button("Back"))
        {
            director().switch_scene<game::MainMenu>();
        }

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

        //Create game
        ImGui::SetCursorPosX(270.);
        if (ImGui::Button("Create game", button_size))
        {
            director().switch_scene<game::InGame>();
        }

        ImGui::Text("%65s", "Press E to break and collect items");
        ImGui::Text("%73s", "Press F to attack enemies (better with a sword :p)");
        ImGui::Text("%60s", "Go to water to drink");
        ImGui::Text("%68s", "Press A to eat some food if you find some");
        ImGui::Text("%65s", "Try not to be killed");
        ImGui::Text("%67s", "Make a boat to escape the island");
        ImGui::Text("%60s", "Good luck !");
        

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
