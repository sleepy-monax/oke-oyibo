#include "core/Camera.h"
#include "core/World.h"

#include "base/components/Momentum.h"
#include "base/components/Move.h"
#include "base/components/Position.h"

#include "base/systems/Movement.h"

namespace base
{
    void Movement::update(core::World &world, core::Time &)
    {
        auto view = world.entities().view<base::Position, base::Momentum, base::Move>();

        view.each([&](base::Position &position, base::Momentum &momentum, base::Move &move) {
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

            auto diff = move.destination - position();

            auto acceleration = diff.normalized();

            momentum.ax = acceleration.x() * move.speed;
            momentum.ay = acceleration.y() * move.speed;
        });
    }

    // void Movement::render(core::World &world, core::Camera &camera)
    // {
    //     auto view = world.entities().view<base::Position, base::Move>();
    //
    //     camera.with_overlay([&]() {
    //         view.each([](base::Position &position, base::Move &move) {
    //             if (!move.moving)
    //             {
    //                 return;
    //             }
    //
    //             DrawLineV({position.x, position.y}, {move.destination.x(), move.destination.y()}, RED);
    //         });
    //     });
    // }
} // namespace base