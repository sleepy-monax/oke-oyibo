#pragma once

#include <vector>

#include "game/inventory/Stack.h"

#include "utils/Vector.h"

namespace game
{
    struct Inventory
    {
        static constexpr int MAX_SIZE = 64;

        utils::Vector<game::Stack> inventory;

        game::Stack add(game::Stack stack)
        {

            for (size_t i = 0; i < inventory.count(); i++)
            {
                if (inventory[i].item().name() == stack.item().name())
                {
                    stack.quantity(inventory[i].add(stack.quantity()));
                }
            }

            if (stack.quantity() > 0 && inventory.count() < MAX_SIZE)
            {
                inventory.push_back(stack);
                stack.quantity(0);
            }

            return stack;
        }

        game::Stack remove(game::Stack stack)
        {
            for (size_t i = 0; i < inventory.count(); i++)
            {
                if (inventory[i].item().name() == stack.item().name())
                {
                    auto quantityRemoved = inventory[i].remove(stack.quantity());
                    stack.quantity(stack.quantity() - quantityRemoved);
                    if (inventory[i].quantity() == 0)
                    {
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

        int count(game::Item item) const
        {
            int result = 0;

            for (size_t i = 0; i < inventory.count(); i++)
            {
                if (inventory[i].item() == item)
                {
                    result += inventory[i].quantity();
                }
            }

            return result;
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
    for (size_t i = 0; i < inv.inventory.count(); i++)
    {
        ImGui::PushID(&inv.inventory[i]);
        inspect(inv.inventory[i]);
        ImGui::PopID();
    }
}