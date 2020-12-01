#pragma once

#include "Item.h"
#include "editor/Inspect.h"

namespace game
{
    class Stack
    {
    private:
        Item item;
        int quantity;
        static constexpr int MAX_QUANTITY = 64;
    public:
        Stack(Item item, int quantity);
        ~Stack();
        friend void inspect<game::Stack>(game::Stack &stack);
        Item getItem() const;
        int getQuantity() const;
        int getMax_quantity() const;
        void add(int quantity);
    };
    
} // namespace game

template<>
inline void inspect<game::Stack>(game::Stack &stack)
{
    ImGui::InputInt("quantity", &stack.quantity);
    ImGui::Text("name  : %s", stack.item.getName().c_str());
}