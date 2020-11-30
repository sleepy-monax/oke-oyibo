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
} // namespace core