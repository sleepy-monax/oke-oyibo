#pragma once

#include <raylib.h>

#include "utils/Rect.h"
#include "utils/Vec.h"

#include "core/Texture.h"

namespace core
{
    void fill_rect(utils::Rectf dest, Color color);

    void draw_rect(utils::Rectf dest, Color color);

    void draw_texture(Texture texture, utils::Rectf src, utils::Rectf dest, Color color);

    void draw_texture(Texture texture, utils::Rectf dest, Color color);

    void draw_ellipse(utils::Vec2f vec, float radiusH, float radiusV, Color color);
} // namespace core
