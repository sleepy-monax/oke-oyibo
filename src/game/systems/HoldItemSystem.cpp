#include "HoldItemSystem.h"

#include "base/components/Player.h"
#include "game/components/HoldItem.h"
#include "game/components/Inventory.h"

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/Scene.h"

namespace game
{
    HoldItemSystem::HoldItemSystem()
    {
    }

    HoldItemSystem::~HoldItemSystem()
    {
    }

    void HoldItemSystem::update(core::World &world, core::Time &)
    {
        auto player = world.entities().view<game::Inventory, game::HoldItem, base::Player>();

        player.each([&](auto &inventory, auto &hold, auto &) {
            if (IsKeyPressed(KEY_SPACE))
            {
                if (hold.index == static_cast<int>(inventory.inventory.size() - 1))
                {
                    hold.index = 0;
                    return;
                }

                for (size_t i = 0; i < inventory.inventory.size(); i++)
                {
                    if (static_cast<size_t>(hold.index) == i - 1)
                    {
                        hold.index = static_cast<int>(i);
                        break;
                    }
                }
            }
        });
    }

    void HoldItemSystem::render(core::World &world, core::Camera &camera)
    {
        auto player = world.entities().view<game::Inventory, game::HoldItem, base::Position>();

        camera.with_entities([&]() {
            player.each([&](auto &inv, auto &hold, auto &position) {
                utils::Rectf bound = {3, -10, 6, 6};

                bound = bound.offset(position.pos2d());

                if (inv.inventory.size() > 0)
                {
                    texture = inv.inventory[hold.index].getItem().get_texture();
                }
                else
                {
                    texture = world.registry().texture("empty");
                }

                core::draw_texture(texture, bound, WHITE);

            });
        });
    }

}; // namespace game
