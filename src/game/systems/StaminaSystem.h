#pragma once

#include <base/components/Acceleration.h>
#include <game/components/Stamina.h>

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game {
    class StaminaSystem : public core::System
    {
        private:
            double _accumulator = 0;
            double _accumAccel = 0;

        public:
            StaminaSystem() 
            {
            }

            void update(core::World &world, core::Time &time)
            {
                auto view = world.entities().view<game::Stamina, base::Acceleration>();

                if (stackFrame(time))
                {
                    view.each([&](game::Stamina &stamina, base::Acceleration &acceleration) {
                        if (acceleration.ax == 0.05f || acceleration.ay == 0.05f || acceleration.ax == -0.05f || acceleration.ay == -0.05f) {
                            if (stamina.current_stamina - 0.8f <= 0) {
                                stamina.current_stamina = 0.0f;
                            } else {
                                stamina.current_stamina -= 0.8f;
                            }
                        }

                        

                        if (acceleration.ax == 0.0f && acceleration.ay == 0.0f) {
                            if (stamina.current_stamina + 0.3f > stamina.max_stamina) {
                                stamina.current_stamina = stamina.max_stamina;
                            } else {
                                stamina.current_stamina += 0.3f;
                            }
                        }
                    });
                }

                if (stackFrameForAcc(time)) {
                    view.each([&](game::Stamina &stamina, base::Acceleration &acceleration) {
                        if (stamina.current_stamina < (stamina.max_stamina)/5) {
                            if (acceleration.ax == 0.05f) {
                                acceleration.ax = 0.02f;
                            } else if (acceleration.ay == 0.05f) {
                                acceleration.ay = 0.02f;
                            } else if (acceleration.ax == -0.05f) {
                                acceleration.ax = -0.02f;
                            } else if (acceleration.ay == -0.05f) {
                                acceleration.ay = -0.02f;
                            }
                        }
                    });
                }
            }

            bool stackFrame(core::Time &time)
            {
                _accumulator += time.elapsed();

                if (_accumulator >= 1)
                {
                    _accumulator -= 1;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            bool stackFrameForAcc(core::Time &time)
            {
                _accumAccel += time.elapsed();

                if (_accumAccel >= 0.05)
                {
                    _accumAccel -= 0.05;
                    return true;
                }
                else
                {
                    return false;
                }
            }


    };
}