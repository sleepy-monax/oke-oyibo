#include <rlgl.h>

#include "core/Graphics.h"

namespace core
{
    Rectangle to_raylib(utils::Rectf r)
    {
        return {
            r.x(),
            r.y(),
            r.width(),
            r.height(),
        };
    }

    void fill_rect(utils::Rectf dest, Color color)
    {
        DrawRectanglePro(to_raylib(dest), {0, 0}, 0, color);
    }

    void draw_rect(utils::Rectf dest, Color color)
    {
        DrawRectangleLinesEx(to_raylib(dest), 1, color);
    }

    void draw_texture(Texture texture, utils::Rectf src, utils::Rectf dest, Color color)
    {
        DrawTexturePro(texture.undelying(), to_raylib(src), to_raylib(dest), {0, 0}, 0, color);
    }

    void draw_texture(Texture texture, utils::Rectf dest, Color color)
    {
        draw_texture(texture, texture.bound(), dest, color);
    }

    void draw_texture_flip(Texture texture, utils::Rectf dest, Color color)
    {
        auto b = texture.bound();
        draw_texture(texture, {b.top_right(), {b.width() * -1.0f, b.height()}}, dest, color);
    }

    void draw_ellipse(utils::Vec2f vec, float radiusH, float radiusV, Color color)
    {
        if (rlCheckBufferLimit(3 * 36))
        {
            rlglDraw();
        }

        rlBegin(RL_TRIANGLES);
        for (int i = 0; i < 360; i += 10)
        {
            rlColor4ub(color.r, color.g, color.b, color.a);
            rlVertex2f(vec.x(), vec.y());
            rlVertex2f(vec.x() + sinf(DEG2RAD * i) * radiusH, vec.y() + cosf(DEG2RAD * i) * radiusV);
            rlVertex2f(vec.x() + sinf(DEG2RAD * (i + 10)) * radiusH, vec.y() + cosf(DEG2RAD * (i + 10)) * radiusV);
        }
        rlEnd();
    }
} // namespace core