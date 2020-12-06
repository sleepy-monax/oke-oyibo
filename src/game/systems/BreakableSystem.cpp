#include "BreakableSystem.h"

#include "base/components/Player.h"

#include "base/components/Position.h"
#include "game/components/Inventory.h"

namespace game
{
    BreakableSystem::BreakableSystem() {}
    BreakableSystem::~BreakableSystem() {}

    void BreakableSystem::update(core::World &world, core::Time &)
    {
        auto player = world.entities().view<game::Inventory, base::Position, base::Player>();
        auto breakable = world.entities().view<game::Breakable, base::Position>();

        player.each([&](auto &, auto &position, auto &pl) {
            auto pos_inventory = position();

            breakable.each([&](auto const &entity, auto &item, auto &position) {
                auto pos_breakable = position();

                if (pos_inventory.distance_to(pos_breakable) <= 8.)
                {
                    if (IsKeyPressed(KEY_E))
                    {
                        item.durability--;
                        auto &camera = world.players()[pl.player_index].camera();

                        camera.trauma(0.01);
                        if (item.durability == 0)
                        {
                            world.create_item(item.stack, position());
                            world.remove_entity(entity);
                        }
                    }
                }
            });
        });
    }
} // namespace game
