#pragma once

#include "core/System.h"

namespace game
{
    class EnemyMove : public core::System{
        private:


        public:
            EnemyMove();
            ~EnemyMove();

            void update(core::World &world, core::Time &time);
    };
} // namespace game
