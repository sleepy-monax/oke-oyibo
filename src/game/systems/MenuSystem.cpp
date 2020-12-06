#include <cmath>
#include <raylib.h>

#include "core/Camera.h"
#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/World.h"

#include "game/components/Menu.h"
#include "game/systems/MenuSystem.h"

namespace game
{
    void MenuSystem::on_load(core::Registry &registry)
    {
        _font = registry.font("romulus");
        _cursor = registry.texture("cursor");
    }

    void MenuSystem::render(core::World &world, core::Camera &camera)
    {
        static constexpr int ITEM_SIZE = 8;
        static constexpr int ITEM_GAP = 2;

        auto view = world.entities().view<game::Menu, base::Position>();
        auto &crafts = world.registry().crafts();

        camera.with_overlay([&]() {
            view.each([&](game::Menu &menu, base::Position &position) {
                utils::Rectf bound = {
                    0,
                    0,
                    ITEM_SIZE * (float)crafts.count() + ITEM_GAP * (float)crafts.count() - 1,
                    ITEM_SIZE,
                };

                bound = bound.offset(position() - bound.center() - utils::Vec2f{0, 8});

                core::draw_rect(bound, RED);

                for (size_t i = 0; i < crafts.count(); i++)
                {
                    auto &craft = crafts[i];
                    auto column = bound.column(crafts.count(), i, ITEM_GAP);

                    if (menu.selected == i)
                    {
                        core::draw_texture(_cursor, column, WHITE);
                    }

                    core::draw_texture(craft.result.item().texture(), column, WHITE);

                    Vector2 pos(column.bottom_left().x() + 4, column.bottom_left().y() - 5);
                    DrawTextEx(_font, std::to_string(craft.result.quantity()).c_str(), pos, 4.f, 1.f, WHITE);
                }

                if (menu.visible)
                {
                }
            });
        });
    }
} // namespace game
