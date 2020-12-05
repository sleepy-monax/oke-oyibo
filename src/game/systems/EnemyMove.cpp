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
    void EnemyMove::update(core::World &world, core::Time &time){
        enemy_random_travel(world, time, 0.1);
        enemy_travel_to_player(world, time, 3, 0.1);
    }


    //The enemy moves on the map
    void EnemyMove::enemy_random_travel(core::World &world, core::Time &time, double enemy_speed){
        auto view_player = world.entities().view<base::Player, base::Position>();
        auto view_enemy = world.entities().view<game::Enemy, base::Position, base::Acceleration>();

        if(stackFrame(time)){
            //Search all player instance
            view_player.each([&](auto &, auto &){
                //Search all enemy instance
                view_enemy.each([&](auto &, auto &, auto &enemy_acceleration){

                    //Random x-axis travel
                    int random_x = rand()%11;
                    int random_y = rand()%11;
                    if(random_x <6){
                        enemy_acceleration.ax += enemy_speed;
                    
                    }else if(random_x>=6){
                        enemy_acceleration.ax -= enemy_speed;  
                    }
                    
                    //Random y-axis travel
                    if(random_y<6){
                        enemy_acceleration.ay += enemy_speed;
                    }else if(random_y>=6){
                        enemy_acceleration.ay -= enemy_speed;
                    }
                });
            });
        }
    }


    //The enemy will focus the player if he enter near him
    void EnemyMove::enemy_travel_to_player(core::World &world, core::Time &time, double enemy_frame_detection, double enemy_speed){
        auto view_player = world.entities().view<base::Player, base::Position>();
        auto view_enemy = world.entities().view<game::Enemy, base::Position, base::Acceleration>();

        if(stackFrame(time)){
            //Search all player instance
            view_player.each([&](auto &, auto &player_position){
                //Search all enemy instance
                view_enemy.each([&](auto &, auto &enemy_position, auto &enemy_acceleration){

                    //The enemy focuses the player and moves to him
                    //Distance calculation between the enemy position and the player position
                    if(sqrt(
                        pow(player_position.x-enemy_position.x,2) 
                        +pow(player_position.y-enemy_position.y,2)
                        )
                        <(core::Tile::SIZE*enemy_frame_detection)){
                        
                        //The enemy goes to the player 
                        utils::Vec2f destination(player_position.x, player_position.y);
                        auto acc = destination - enemy_position.pos2d();
                        acc = acc.normalized();
                        enemy_acceleration.ax = acc.x()*enemy_speed;
                        enemy_acceleration.ay = acc.y()*enemy_speed;
                    }
                });
            });
        }
    }


    //Speed of each frame
    bool EnemyMove::stackFrame(core::Time &time)
    {
        _accumulator += time.elapsed();
        if (_accumulator >= 2)
        {
            _accumulator -= 0.1;
            return true;
        }
        else
        {
            return false;
        }
    }
} // namespace game

