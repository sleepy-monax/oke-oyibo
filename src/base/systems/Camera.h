#pragma once

#include "core/System.h"

namespace base
{
    class Camera: public core::System
    {
        void update(core::World &world, core::Time &time) override;
    };
} // namespace base