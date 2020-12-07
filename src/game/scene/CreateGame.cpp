#include <imgui.h>

#include "CreateGame.h"
#include "core/Graphics.h"
#include "game/scene/InGame.h"

#include "core/Camera.h"
#include "core/glue/ImGuiExtension.h"
#include "game/generator/Generator.h"

#include "game/generator/Generator.h"
#include "core/Camera.h"
#include "core/Keyboard.h"

namespace game
{
    CreateGame::CreateGame(core::Director &dir, core::Registry &reg) :
        core::Scene(dir, reg)
    {
    }

    CreateGame::~CreateGame()
    {
    }

    void CreateGame::update(core::Time &time)
    {
        Scene::update(time);
        _camera.resize_to_fit_the_screen();

        _camera.animate(time.elapsed());
        _camera.speed(0.07f);

        if (stackFrame(time))
        {
            int randomX = rand() % ((int)_world->terrain().bound().width() - (int)_camera.bound_world().width());
            int randomY = rand() % ((int)_world->terrain().bound().height() - (int)_camera.bound_world().height());

            _camera.move_to({(float)randomX + (_camera.bound_world().width() / 2),
                             (float)randomY + (_camera.bound_world().height() / 2)});
        }

        _world->update(time);
    }

    void CreateGame::render()
    {
        _camera.clear();
        _world->render(_camera);
        _camera.compose();

        Rectangle rect{0, 0, _camera.width() * 1.0f, _camera.height() * 1.0f};
        DrawTexturePro(_camera.composite().underlying_texture(), rect, rect, (Vector2){0, 0}, 0.0f, WHITE);

        //Create menu window
        ImGui::Begin("Create game");
        ImVec2 vector(720, 340), button_size(200, 30);
        ImGui::SetWindowSize(vector);

        ImGui::Text("%65s", "Welcome to Oke Oyibo ! ");

        //Name of the world
        ImGui::Text("%20s", "Name of the world : ");
        ImGui::SameLine();
        char buf[64] = "";
        ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

        //Difficulty
        ImGui::Text("%20s", "Difficulty : ");
        ImGui::SameLine();
        //static int animate = 1;
        const char *difficulties[] = {"easy", "normal", "hard"};
        static int difficulty_current_index = 0;
        const char* combo_difficulties = difficulties[difficulty_current_index];
        //ImGui::Comworld->add_player({"bob", utils::own<core::Keyboard>()});
        
        if (ImGui::BeginCombo(" ", combo_difficulties, 0))
        {
            for (int n = 0; n < IM_ARRAYSIZE(difficulties); n++)
            {
                const bool is_selected = (difficulty_current_index == n);
                if (ImGui::Selectable(difficulties[n], is_selected)){
                    difficulty_current_index = n;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        //Create a game

        ImGui::Text(" ");
        ImGui::TextCenter("Press E to break and collect items");
        ImGui::TextCenter("Press J to attack enemies (better with a sword :p)");
        ImGui::TextCenter("Press A to eat some food if you find some");
        ImGui::TextCenter("Press Up Arrow to see the craft recipes");
        ImGui::TextCenter("Press Enter to confirm the craft");
        ImGui::TextCenter("Go to water to drink");
        ImGui::TextCenter("Try not to be killed");
        ImGui::TextCenter("Make a boat to escape the island");
        ImGui::TextCenter("Good luck !");
        ImGui::Text(" ");

        ImGui::SetCursorPosX(270.);
        if (ImGui::Button("Create game", button_size))
        {
            Generator gen{};

            auto world = gen.generate(registry(), time(nullptr));

            world->add_player({"bob", utils::own<core::Keyboard>()});
            world->players()[0].camera().zoom_in();
            world->players()[0].camera().speed(10);
            world->players()[0].camera().jump_to(world->terrain().bound().center());

            world->create_entity(registry().blueprint("player"), world->terrain().bound().center());
            world->setDifficulty(difficulty_current_index);
            director().switch_scene<game::InGame>(world);
        }

        ImGui::End();
    }

    void CreateGame::on_switch_in()
    {
        Scene::on_switch_in();
        Generator gen{};

        _world = gen.generate(registry(), time(nullptr));
        _camera.jump_to(_world->terrain().bound().center());
    }

    void CreateGame::on_switch_out()
    {
        Scene::on_switch_out();
    }

    bool CreateGame::stackFrame(core::Time &time)
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
} // namespace game