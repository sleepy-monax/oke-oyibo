#pragma once

#include <raylib.h>

#include "utils/Rect.h"

namespace core
{
    class Texture
    {
    private:
        Texture2D _tex{};

    public:
        utils::Rectf bound()
        {
            return {0, 0, (float)_tex.width, (float)_tex.height};
        }

        Texture2D &undelying()
        {
            return _tex;
        }

        Texture() {}

        Texture(Texture2D tex) :
            _tex(tex)
        {
        }
    };

} // namespace core
