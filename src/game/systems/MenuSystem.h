#pragma once

#include "core/System.h"
#include "core/Texture.h"

namespace game
{
    class MenuSystem: public core::System
    {
        Font _font;
        core::Texture _cursor;

        void on_load(core::Registry &registry);

        void render(core::World &, core::Camera &) override;
    };
} // namespace game
