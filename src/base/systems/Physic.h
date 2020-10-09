#pragma once

#include "base/components/Acceleration.h"
#include "base/components/Position.h"
#include "base/components/Velocity.h"
#include "core/System.h"
#include "core/World.h"
#include "editor/Inspect.h"

namespace base
{
    class Physic : public core::System
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

        void update(core::World &world, core::UpdateContext &context) override
        {
            auto view = world.entities().view<Acceleration, Velocity, Position>();

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

        friend void inspect<base::Physic>(base::Physic &physic);
    };
} // namespace base

template <>
void inspect<base::Physic>(base::Physic &physic)
{
    ImGui::SliderFloat("Air Friction", &physic._air_friction, 0, 1, "Friction %f", 0);
    ImGui::SliderFloat("Time step", &physic._time_scale, 0, 1, "%fsec", 0);
}
