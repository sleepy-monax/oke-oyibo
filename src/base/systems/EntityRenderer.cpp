#include <raylib.h>

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/World.h"

#include "base/components/Position.h"
#include "base/components/Sprite.h"
#include "base/systems/EntityRenderer.h"

namespace base
{
    void EntityRenderer::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<Position, Sprite>();

        camera.with_entities([&]() {
            view.each([&](auto &position, auto &sprite) {
                auto tex = sprite.texture;

                auto destination = tex.bound().moved(position.pos2d() - tex.bound().bottom_center());

                if (destination.colide_with(camera.bound_world()))
                {
                    core::draw_texture(tex, destination, WHITE);
                }
            });
        });
    }
} // namespace base
