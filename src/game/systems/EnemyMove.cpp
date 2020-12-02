#include "EnemyMove.h"

#include <raylib.h>
#include <cmath>

#include "base/components/Position.h"
#include "base/components/Acceleration.h"
#include "base/components/Player.h" 

#include "core/World.h"
#include "core/Tile.h"

#include "game/components/Enemy.h"

namespace game
{
    EnemyMove::EnemyMove(){

    }

    EnemyMove::~EnemyMove(){

    }

    //enemy movements
    void EnemyMove::update(core::World &world, core::Time &){
        auto view_player = world.entities().view<base::Player, base::Position>();
        auto view_enemy = world.entities().view<game::Enemy, base::Position, base::Acceleration>();

        //Get terrain size
        int map_width = world.terrain().bound().width();
        int map_height = world.terrain().bound().height();

        //Search all player instance
        view_player.each([&](auto &, auto &player_position){
            //Search all enemy instance
            view_enemy.each([&](auto &, auto &enemy_position, auto &enemy_acceleration){
                
                //The enemy moves randomly
                utils::Vec2f destination(rand() % map_width, rand() % map_height);
                auto acc = destination - enemy_position.pos2d();
                acc = acc.normalized();
                enemy_acceleration.ax = acc.x()/50;
                enemy_acceleration.ay = acc.y()/50;

                //The enemy focuses the player and moves to him
                //Distance calculation between the enemy position and the player position
                if(sqrt(
                        pow(player_position.x-enemy_position.x,2) 
                        +pow(player_position.y-enemy_position.y,2)
                    )
                    <(core::Tile::SIZE*5)){
                    
                    //The enemy goes to the player 
                    utils::Vec2f destination(player_position.x, player_position.y);
                    auto acc = destination - enemy_position.pos2d();
                    acc = acc.normalized();
                    enemy_acceleration.ax = acc.x()/50;
                    enemy_acceleration.ay = acc.y()/50;
                }
            });
        });
    }
} // namespace game

