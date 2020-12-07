#pragma once

#include "utils/Vector.h"

#include "game/components/Inventory.h"
#include "game/inventory/Craft.h"

namespace game
{
    struct Craft
    {
        Stack result;
        utils::Vector<Stack> ingredients;

        bool can_be_made(Inventory inv) const
        {
            for (size_t i = 0; i < ingredients.count(); i++)
            {
                if (inv.count(ingredients[i].item()) < ingredients[i].quantity())
                {
                    return false;
                }
            }

            return true;
        }

        void do_it(Inventory &inv) const
        {
            if (can_be_made(inv))
            {
                for (size_t i = 0; i < ingredients.count(); i++)
                {
                    inv.remove(ingredients[i]);
                }

                inv.add(result);
            }
        }
    };
} // namespace game
