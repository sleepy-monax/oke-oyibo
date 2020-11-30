#pragma once

#include <raylib.h>

#include "core/Registry.h"
#include "core/System.h"
#include "core/World.h"

#include "base/components/Position.h"
#include "base/components/Sprite.h"

namespace base
{
    class EntityRenderer: public core::System
    {
    private:
    public:
        EntityRenderer()
        {
        }

        void render(core::World &world, core::Camera &camera) override
        {
            auto view = world.entities().view<Position, Sprite>();

            camera.with_entities([&]() {
                view.each([&](auto &position, auto &sprite) {
                    auto tex = world.registry().texture(sprite.handle);

                    DrawTextureEx(tex, {position.x - tex.width / 2.0f, position.y - tex.height}, 0.0, 1, WHITE);
                });
            });
        }
    };
} // namespace base