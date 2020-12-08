#include <imgui.h>

#include "CreateGame.h"
#include "core/Graphics.h"
#include "game/scene/InGame.h"

#include "core/Camera.h"
#include "core/glue/ImGuiExtension.h"
#include "game/generator/Generator.h"

#include "core/Camera.h"
#include "core/Keyboard.h"
#include "base/components/Player.h"
#include "game/generator/Generator.h"

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

        float menu_with = MeasureTextEx(_font, "Oke-Oyibo", 72, 1).x + 128;
        float title_height = MeasureTextEx(_font, "Oke-Oyibo", 72, 1).y + 72;
        DrawRectangle(0, 0, menu_with, _camera.height(), {0, 0, 0, 200});
        DrawTextEx(_font, "Oke-Oyibo", {64, 64}, 72, 1, WHITE);

        //Create menu window
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::Begin("Create game", nullptr, window_flags);
        ImVec2 vector(menu_with - 128, _camera.height()), button_size(menu_with - 128, 32);
        ImGui::SetWindowSize(vector);

        ImVec2 pos{64, title_height};
        ImGui::SetWindowPos(pos);

        ImGui::Text("Welcome to Oke-Oyibo!");

        ImGui::Text(" ");

        //Name of the world
        ImGui::Text("Name of the world : ");

        static char buf[64] = "";
        ImGui::InputText("", buf, IM_ARRAYSIZE(buf));

        //Difficulty
        ImGui::Text("Difficulty :");

        static const char *difficulties[] = {"easy", "normal", "hard"};
        static int difficulty_current_index = 0;
        const char *combo_difficulties = difficulties[difficulty_current_index];

        if (ImGui::BeginCombo(" ", combo_difficulties, 0))
        {
            for (int n = 0; n < IM_ARRAYSIZE(difficulties); n++)
            {
                const bool is_selected = (difficulty_current_index == n);
                if (ImGui::Selectable(difficulties[n], is_selected))
                {
                    difficulty_current_index = n;
                }
            }
            ImGui::EndCombo();
        }

        static float world_scale = 1;
        ImGui::PushID("scale");
        ImGui::Text("Scale :");
        ImGui::SliderFloat("", &world_scale, 1, 5, "x%f", 0);
        ImGui::PopID();

        //Create a game

        ImGui::Text(" ");
        ImGui::TextCenter("Press J to break items");
        ImGui::TextCenter("Press J to attack enemies (better with a sword :p)");
        ImGui::TextCenter("Press A to eat some food if you find some");
        ImGui::TextCenter("Press Up Arrow to see the craft recipes");
        ImGui::TextCenter("Press Enter to confirm the craft");
        ImGui::TextCenter("Go to water to drink");
        ImGui::TextCenter("Try not to be killed");
        ImGui::TextCenter("Make a boat to escape the island");
        ImGui::TextCenter("Good luck !");
        ImGui::Text(" ");

        ImGui::SetCursorPosX(0);
        if (ImGui::Button("Create game", button_size))
        {
            Generator gen{};

            auto world = gen.generate(registry(), 128 * world_scale, time(nullptr));

            world->add_player({"bob", utils::own<core::Keyboard>()});
            world->players()[0].camera().zoom_in();
            world->players()[0].camera().speed(10);
            world->players()[0].camera().jump_to(world->terrain().bound().center());

            // FIXME: multiplayer.
            // world->add_player({"greg", utils::own<core::Keyboard>()});
            // world->players()[1].camera().zoom_in();
            // world->players()[1].camera().speed(10);
            // world->players()[1].camera().jump_to(world->terrain().bound().center());

            world->create_entity(registry().blueprint("player"), world->terrain().bound().center());
            // world->create_entity(registry().blueprint("player"), world->terrain().bound().center() + utils::Vec2f{64,64}).with<base::Player>(1);
            world->setDifficulty(difficulty_current_index);

            director().switch_scene<game::InGame>(world);
        }

        ImGui::End();
    }

    void CreateGame::on_switch_in()
    {
        Scene::on_switch_in();
        Generator gen{};

        _font = registry().font("alagard");
        _world = gen.generate(registry(), 128, time(nullptr));
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