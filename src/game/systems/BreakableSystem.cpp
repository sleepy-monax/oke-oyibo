#include "BreakableSystem.h"

#include "base/components/Position.h"
#include "game/components/Inventory.h"

namespace game
{
    BreakableSystem::BreakableSystem() {}
    BreakableSystem::~BreakableSystem() {}

    void BreakableSystem::update(core::World &world, core::Time &){
        auto player = world.entities().view<game::Inventory,base::Position>();
        auto breakable = world.entities().view<game::Breakable, base::Position>();

        player.each([&](auto &inventory, auto &position) {
            auto pos_inventory = position.pos2d();

            breakable.each([&](auto const &entity, auto &item, auto &position) {
                auto pos_breakable = position.pos2d();

                if (pos_inventory.distance_to(pos_breakable) <=6.)
                {
                    if (IsKeyPressed(KEY_E))
                    {
                        item.durability--;
                        if (item.durability == 0)
                        {
                            world.remove_entity(entity);
                            inventory.add(item.stack);
                        }
                    }
                    
                }
                
            });
        });
    }
} // namespace game
