#include <imgui.h>

#include "core/Director.h"
#include "EndGameScene.h"
#include "core/Graphics.h"
#include "game/scene/CreateGame.h"
#include "core/Camera.h"
#include "core/glue/ImGuiExtension.h"
#include "game/generator/Generator.h"

#include "game/generator/Generator.h"
#include "core/Camera.h"

namespace game
{
    EndGameScene::EndGameScene(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg)
    {
    }

    EndGameScene::~EndGameScene()
    {
    }

    void EndGameScene::render()
    {
        //Create menu window
        ImGui::Begin("End game");
        ImVec2 vector(720, 340), button_size(200, 30);
        ImGui::SetWindowSize(vector);

        ImGui::TextCenter("Good job ! ");
        ImGui::TextCenter("You have finished the game :)");

        ImGui::SetCursorPosX(270.);
        if (ImGui::Button("Go to main menu", button_size))
        {
            director().switch_scene<game::CreateGame>();
        }

        ImGui::End();
    }

    void EndGameScene::on_switch_in()
    {
        Scene::on_switch_in();
    }

    void EndGameScene::on_switch_out()
    {
        Scene::on_switch_out();
    }

    bool EndGameScene::stackFrame(core::Time &time)
    {
        _accumulator += time.elapsed();

        if (_accumulator >= 4)
        {
            _accumulator -= 4;
            return true;
        }
        else
        {
            return false;
        }
    }
}