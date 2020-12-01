#pragma once

#include "core/System.h"

namespace base
{
    class Input: public core::System
    {
        void update(core::World &world, core::Time &) override;
    };
} // namespace base
