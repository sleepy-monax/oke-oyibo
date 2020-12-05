#include "core/Graphics.h"
#include "core/Registry.h"

#include "base/components/Acceleration.h"
#include "base/components/Player.h"

#include "game/components/Enemy.h"

#include "game/systems/ReviveSystem.h"

#include <imgui.h>

namespace game
{
    ReviveSystem::ReviveSystem() 
    {
    }

    void ReviveSystem::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<base::Player, game::Health, game::Hunger, game::Thirst, base::Acceleration, game::Inventory, game::Stamina>();
        camera.with_overlay([&]() {
            view.each([&](auto &, auto &health, auto &hunger, auto &thirst, auto &acceleration, auto &inventory, auto &stamina) {
                if (health.health == 0) {

                    acceleration.ax = 0.0f;
                    acceleration.ay = 0.0f;

                    kill_enemy(world);

                    ImGui::Begin("Retry");

                    ImVec2 vector(400, 180), button_size(170,30);
                    ImGui::SetWindowSize(vector);

                    //You are dead
                    ImGui::Text("%35s", "YOU ARE DEAD !");

                    //Retry ?
                    ImGui::Text("%45s", "You'll be luckier next time ...");

                    //Back to menu
                    ImGui::SetCursorPosX(27.);
                    ImGui::SetCursorPosY(120.);
                    if (ImGui::Button("Retry without inventory", button_size))
                    {
                        inventory.clear();
                        reset(health, hunger, thirst, stamina);
                    }

                    //Retry 
                    ImGui::SameLine();
                    if (ImGui::Button("Retry with inventory", button_size))
                    {
                        reset(health, hunger, thirst, stamina);
                    }

                    ImGui::End();

                }
            });
        });
    }
    
    void ReviveSystem::reset(game::Health &health, game::Hunger &hunger, game::Thirst &thirst, game::Stamina &stamina) {
        health.health = health.maxHealth;
        hunger.current_food = hunger.max_food;
        thirst.current_thirst = thirst.max_thirst;
        stamina.current_stamina = stamina.max_stamina;
    }

    void ReviveSystem::kill_enemy(core::World &world)
    {
        auto enemy = world.entities().view<game::Enemy, base::Position>();
        auto player = world.entities().view<base::Player, base::Position>();

        enemy.each([&](auto const &entity, auto &, auto &positionEnemy)
        {
            auto enemy_pos = positionEnemy.pos2d();
            player.each([&](auto &, auto &positionPlayer)
            {
                auto player_pos = positionPlayer.pos2d();

                if (enemy_pos.distance_to(player_pos) <= 100) 
                {
                    world.remove_entity(entity);
                }
            });
        });
    }
}