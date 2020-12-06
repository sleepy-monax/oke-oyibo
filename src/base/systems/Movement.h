#pragma once

#include "core/System.h"

namespace base
{
    class Movement: public core::System
    {
        void update(core::World &, core::Time &) override;

        // void render(core::World &, core::Camera &) override;
    };
} // namespace base
