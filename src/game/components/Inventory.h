#pragma once

#include <vector>

#include "game/inventory/Stack.h"

namespace game
{
    struct Inventory
    {
        std::vector<game::Stack> inventory;
        static constexpr int MAX_SIZE = 64;

        void add(game::Stack &stack) {
            
            if (inventory.size() >= MAX_SIZE)
            {
                return;
            }
            

            bool find = false;
            for (game::Stack &st : inventory)
            {
                if (st.getItem().getName() == stack.getItem().getName())
                {
                    st.add(stack.getQuantity());
                    find = true;
                }
            }

            if (!find)
            {
                inventory.push_back(stack);
            }
            
            
            
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