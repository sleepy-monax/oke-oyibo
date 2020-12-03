#include "HoldItemSystem.h"

#include "base/components/Player.h"
#include "game/components/HoldItem.h"
#include "game/components/Inventory.h"

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

}; // namespace game
