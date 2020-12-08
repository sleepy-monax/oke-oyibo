#include "core/Camera.h"
#include "core/World.h"

#include "base/components/Momentum.h"
#include "base/components/Move.h"
#include "base/components/Position.h"
#include "game/components/Stamina.h"

#include "base/systems/Movement.h"

namespace base
{
    void Movement::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<base::Position, base::Momentum, base::Move>();

        view.each([&](entt::entity entity, base::Position &position, base::Momentum &momentum, base::Move &move) {
            if (!move.moving)
            {
                return;
            }

            if (position().distance_to(move.destination) < core::Tile::SIZE / 2)
            {
                move.moving = false;
                return;
            }

            if (!world.terrain().bound().contains(move.destination))
            {
                move.moving = false;
                return;
            }

            auto speed = move.speed;

            if (world.entities().has<game::Stamina>(entity))
            {
                auto stamina = world.entities().get<game::Stamina>(entity);

                if (stamina.current < (stamina.maximum) / 5)
                {
                    speed /= 2;
                }
            }

            auto diff = move.destination - position();

            auto acceleration = diff.normalized();

            momentum.ax = acceleration.x() * speed;
            momentum.ay = acceleration.y() * speed;
        });
    }
} // namespace base