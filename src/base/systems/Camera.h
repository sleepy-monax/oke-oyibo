#pragma once

#include "core/System.h"

namespace base
{
    class Camera: public core::System
    {
        void update(core::World &world, core::Time &time) override;

        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace base