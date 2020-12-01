#pragma once

#include "core/System.h"

namespace base
{
    class DebugRender: public core::System
    {
        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace base
