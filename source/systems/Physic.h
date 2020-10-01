#pragma once

#include "components/Acceleration.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "systems/System.h"
#include "world/World.h"

namespace systems
{
    class Physic : public System
    {
    private:
        float _air_friction = 0.9;
        float _time_scale = 1 / 60.0;

    public:
        Physic() : System("Physic")
        {
        }

        ~Physic()
        {
        }

        void update(
            world::World &world,
            game::UpdateContext &context) override
        {
            __unused(context);

            auto view = world.entities().view<components::Acceleration, components::Velocity, components::Position>();

            view.each([&](auto &acceleration, auto &velocity, auto &position) {
                velocity.vx += acceleration.ax * (context.elapsed_time() / _time_scale);
                velocity.vy += acceleration.ay * (context.elapsed_time() / _time_scale);

                acceleration.ax = 0;
                acceleration.ay = 0;

                position.x += velocity.vx * (context.elapsed_time() / _time_scale);
                position.y += velocity.vy * (context.elapsed_time() / _time_scale);

                velocity.vx *= (1 - _air_friction) * (context.elapsed_time() / _time_scale);
                velocity.vy *= (1 - _air_friction) * (context.elapsed_time() / _time_scale);
            });
        }

        void display(world::World &) override
        {
            ImGui::SliderFloat("Air Friction", &_air_friction, 0, 1, "Friction %f", 0);
            ImGui::SliderFloat("Time step", &_time_scale, 0, 1, "%fsec", 0);
        }
    };
} // namespace systems
