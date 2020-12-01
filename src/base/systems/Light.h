#pragma once

#include "core/System.h"

namespace base
{
    class Light: public core::System
    {
    private:
    public:
        Light()
        {
        }

        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace base