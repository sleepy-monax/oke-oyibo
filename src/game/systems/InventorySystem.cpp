#include "InventorySystem.h"

#include "game/components/Pickable.h"
#include "base/components/Position.h"

namespace game
{
    InventorySystem::InventorySystem(){
    }
    InventorySystem::~InventorySystem(){}

    void InventorySystem::update(core::World &world, core::Time &) {
        auto player = world.entities().view<game::Inventory, base::Position>();
        auto items = world.entities().view<game::Pickable,base::Position>();

        player.each([&](auto &inventory, auto &position) {
           auto pos_inventory = position.pos2d();

            items.each([&](const auto entity, auto &pickable, auto &position) {
                auto pos_item = position.pos2d();

                if (pos_item.distance_to(pos_inventory) <= 2.)
                {
                    pickable.stack = inventory.add(pickable.stack);
                    if(pickable.stack.getQuantity() == 0 )
                    {
                        world.remove_entity(entity);
                    }
                }
                 
            });
        });
        
    }
} // namespace game
