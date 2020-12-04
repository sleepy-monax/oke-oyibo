#pragma once

#include "core/System.h"

namespace base
{
    class Shadow: public core::System
    {
    private:
    public:
        Shadow()
        {
        }

        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace base