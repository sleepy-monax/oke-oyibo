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

        auto view = world.entities().view<game::Menu, game::Inventory, base::Position>();
        auto &crafts = world.registry().crafts();

        camera.with_overlay([&]() {
            view.each([&](game::Menu &menu, game::Inventory &inventory, base::Position &position) {
                utils::Rectf bound = {
                    0,
                    0,
                    ITEM_SIZE * (float)crafts.count() + ITEM_GAP * (float)crafts.count() - 1,
                    ITEM_SIZE,
                };

                menu.selected = MAX(0, menu.selected);
                menu.selected = MIN(menu.selected, static_cast<int>(crafts.count()) - 1);

                bound = bound.offset(position() - bound.center() + utils::Vec2f{0, 16});

                if (menu.visible)
                {
                    for (int i = 0; i < static_cast<int>(crafts.count()); i++)
                    {
                        auto &craft = crafts[i];
                        auto column = bound.column(crafts.count(), i, ITEM_GAP);

                        if (craft.can_be_made(inventory))
                        {
                            core::draw_texture(craft.result.item().texture(), column, WHITE);
                        }
                        else
                        {
                            core::draw_texture(craft.result.item().texture(), column, {50, 50, 50, 255});
                        }

                        Vector2 pos(column.bottom_left().x() + 6, column.bottom_left().y() - 2);
                        DrawTextEx(_font, std::to_string(craft.result.quantity()).c_str(), pos, 6.f, 1.f, WHITE);

                        if (menu.selected == i)
                        {
                            core::draw_texture(_cursor, column, WHITE);

                            if (menu.clicked)
                            {
                                craft.do_it(inventory);
                                menu.clicked = false;
                                menu.visible = false;
                            }
                        }
                    }
                }

                menu.clicked = false;
            });
        });
    }
} // namespace game
