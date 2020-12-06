#pragma once

#include "core/Texture.h"

namespace game
{
    class MenuLevel
    {
        MenuLevel() {}
        virtual ~MenuLevel() {}

        virtual std::string text(size_t index){};
        virtual core::Texture icon(size_t index){};
        virtual action(size_t index);
        virtual size_t count();
    };
} // namespace game
