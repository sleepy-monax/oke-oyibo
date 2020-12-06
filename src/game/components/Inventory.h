#pragma once

#include <vector>

#include "game/inventory/Stack.h"

namespace game
{
    struct Inventory
    {
        std::vector<game::Stack> inventory;
        static constexpr int MAX_SIZE = 64;

        game::Stack add(game::Stack stack) {

            for (game::Stack &st : inventory)
            {
                if (st.getItem().getName()== stack.getItem().getName())
                {
                    stack.set_quantity(st.add(stack.getQuantity()));
                    
                }
            }

            if (stack.getQuantity() > 0 && inventory.size() < MAX_SIZE)
            {
                inventory.push_back(stack);
                stack.set_quantity(0);
            }
            
            return stack;
        }

        game::Stack remove(game::Stack stack) {
            if (stack.getQuantity() > 0) {
                stack.set_quantity(stack.getQuantity()-1);
            }
            
            return stack;
        }

        void clear() {
            inventory.clear();
        }
    };
} // namespace game

template<>
inline void inspect<game::Inventory>(game::Inventory &inv)
{
    for (game::Stack &stack: inv.inventory)
    {
        ImGui::PushID(&stack);
        inspect(stack);
        ImGui::PopID();
    }
    
}