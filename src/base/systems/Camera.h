#pragma once

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "core/System.h"
#include "core/World.h"

namespace base
{
    class Camera: public core::System
    {
    private:
    public:
        Camera() :
            System("Camera")
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

            camera.with_overlay([&]() {
                view.each([&](base::Player &player) {
                    if (player.player_index >= 0 &&
                        (size_t)player.player_index < world.players().count())
                    {
                        auto &camera = world.players()[player.player_index].camera();

                        DrawCircleLines(camera.target().x(), camera.target().y(), 16, BLUE);
                        DrawCircle(camera.current().x(), camera.current().y(), 4, ORANGE);

                        auto r = camera.bound_world();
                        DrawRectangleLinesEx({r.x(), r.y(), r.width(), r.height()}, 1, RED);
                    }
                });
            });
        }
    };

} // namespace base