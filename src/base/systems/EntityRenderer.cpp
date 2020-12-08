#include <raylib.h>

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/World.h"

#include "base/components/Momentum.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"
#include "base/systems/EntityRenderer.h"

namespace base
{
    struct TextureDestinationPosition
    {
        core::Texture texture;
        utils::Rectf destination;
        Position position;
        bool flash;
        bool flip;
    };

    void EntityRenderer::update(core::World &world, core::Time &time)
    {
        auto view = world.entities().view<Sprite>();

        view.each([&](auto &sprite) {
            sprite.flash -= time.elapsed();
        });
    }

    void EntityRenderer::render(core::World &world, core::Camera &camera)
    {
        auto view = world.entities().view<Position, Sprite>();

        utils::Vector<TextureDestinationPosition> on_screen_sprites{};

        view.each([&](auto &entity, auto &position, auto &sprite) {
            auto tex = sprite.texture;

            auto destination = tex.bound().moved(position() - tex.bound().bottom_center());

            bool flip = false;

            if (world.entities().has<base::Momentum>(entity))
            {
                base::Momentum mom = world.entities().get<base::Momentum>(entity);

                if (mom.vx < 0)
                {
                    flip = true;
                }
            }

            // Only rendere entities which are in the view of the camera.
            if (destination.colide_with(camera.bound_world()))
            {
                on_screen_sprites.push_back({tex, destination, position, sprite.flash > 0, flip});
            }
        });

        if (on_screen_sprites.count() > 0)
        {
            // Sort entities back to front.
            for (size_t i = 0; i < on_screen_sprites.count() - 1; i++)
            {
                for (size_t j = i + 1; j < on_screen_sprites.count(); j++)
                {
                    if (on_screen_sprites[i].position.y > on_screen_sprites[j].position.y)
                    {
                        std::swap(on_screen_sprites[i], on_screen_sprites[j]);
                    }
                }
            }

            camera.with_entities([&]() {
                for (size_t i = 0; i < on_screen_sprites.count(); i++)
                {
                    Color color = WHITE;

                    // When entities are hit they flash red.
                    if (on_screen_sprites[i].flash)
                    {
                        color = RED;
                    }

                    if (on_screen_sprites[i].flip)
                    {
                        core::draw_texture_flip(on_screen_sprites[i].texture, on_screen_sprites[i].destination, color);
                    }
                    else
                    {
                        core::draw_texture(on_screen_sprites[i].texture, on_screen_sprites[i].destination, color);
                    }
                }
            });
        }
    }
} // namespace base
