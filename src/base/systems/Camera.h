#pragma once

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "core/System.h"
#include "core/World.h"

namespace base
{
    class Camera : public core::System
    {
    private:
    public:
        Camera() : System("Camera")
        {
        }

        ~Camera() override
        {
        }

        void update(core::World &world, core::Time &time)
        {
            auto view = world.entities().view<base::Position, base::Player>();

            view.each([&](base::Position &position, base::Player &player) {
                if (player.player_index >= 0 &&
                    (size_t)player.player_index < world.players().count())
                {
                    auto &camera = world.players()[player.player_index].camera();

                    camera.move_to(position.x, position.y);
                    camera.animate(time.elapsed());
                }
            });
        }

        void render(core::World &world, core::Camera &camera) override
        {
            auto view = world.entities().view<base::Player>();

            camera.overlay().use_and_do([&]() {
                view.each([&](base::Player &player) {
                    if (player.player_index >= 0 &&
                        (size_t)player.player_index < world.players().count())
                    {
                        auto &camera = world.players()[player.player_index].camera();

                        DrawCircle(camera.target().x(), camera.target().y(), 4, BLUE);
                        DrawCircle(camera.current().x(), camera.current().y(), 4, ORANGE);

                        auto r = camera.bound();
                        DrawRectanglePro({r.x(), r.y(), r.width(), r.height()}, {}, 0, RED);
                    }
                });
            });
        }
    };

} // namespace base