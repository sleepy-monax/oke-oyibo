#pragma once

#include <vector>

#include "game/inventory/Stack.h"

#include "utils/Vector.h"

namespace game
{
    struct Inventory
    {
        utils::Vector<game::Stack> inventory;
        static constexpr int MAX_SIZE = 64;

        game::Stack add(game::Stack stack)
        {

            for (size_t i=0; i < inventory.count() ; i++)
            {
                if (inventory[i].getItem().getName() == stack.getItem().getName())
                {
                    stack.set_quantity(inventory[i].add(stack.getQuantity()));
                }
            }

            if (stack.getQuantity() > 0 && inventory.count() < MAX_SIZE)
            {
                inventory.push_back(stack);
                stack.set_quantity(0);
            }

            return stack;
        }

        game::Stack remove(game::Stack &stack)
        {
            for (size_t i=0; i<inventory.count();i++)
            {
                if (inventory[i].getItem().getName() == stack.getItem().getName())
                {
                    auto quantityRemoved = inventory[i].remove(stack.getQuantity());
                    stack.set_quantity(stack.getQuantity()-quantityRemoved);
                    if (inventory[i].getQuantity() == 0) {
                        inventory.remove_index(i);
                    }
                }
            }

            return stack;
        }

        game::Stack remove(game::Item item, int quantity)
        {
            game::Stack stack{item, quantity};
            return remove(stack);
        }

        void clear()
        {
            inventory.clear();
        }
    };
} // namespace game

template <>
inline void inspect<game::Inventory>(game::Inventory &inv)
{
    for (size_t i=0; i< inv.inventory.count();i++)
    {
        ImGui::PushID(&inv.inventory[i]);
        inspect(inv.inventory[i]);
        ImGui::PopID();
    }
}