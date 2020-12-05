#include "core/World.h"

#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/systems/Camera.h"

namespace base
{
    void Camera::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<base::Position, base::Player>();

        view.each([&](base::Position &position, base::Player &player) {
            if (player.player_index >= 0 &&
                (size_t)player.player_index < world.players().count())
            {
                auto &camera = world.players()[player.player_index].camera();
                auto world_bound = world.terrain().bound();
                auto camera_allowed_bound = world_bound.shrinked(camera.bound_world().size() / 2);

                if (world.terrain().bound().width() < camera.width_world() || world.terrain().bound().height() < camera.height_world())
                {
                    camera.move_to(position.pos2d());
                }
                else
                {
                    camera.move_to(position.pos2d().clamped(camera_allowed_bound.top_left(), camera_allowed_bound.bottom_right()));
                }

                camera.animate(time.elapsed());
            }
        });
    }
} // namespace base
