#pragma once

#include "core/System.h"

namespace game
{
    class EnemyMove : public core::System{
        private:
            double _accumulator = 0;

        public:
            EnemyMove();
            ~EnemyMove();

            void update(core::World &world, core::Time &time);
            bool stackFrame(core::Time &time);
            void enemy_random_travel(core::World &world, core::Time &time, double enemy_speed);
            void enemy_travel_to_player(core::World &world, core::Time &time, double enemy_frame_detection, double enemy_speed);
    };
} // namespace game
