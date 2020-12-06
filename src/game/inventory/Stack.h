#pragma once

#include "Item.h"
#include "editor/Inspect.h"

namespace game
{
    class Stack
    {
    private:
        Item _item;
        int _quantity = 0;

    public:
        static constexpr auto MAX_QUANTITY = 64;

        Stack(Item item, int quantity);

        ~Stack();

        Item item() const;

        int quantity() const;

        void quantity(int quantity);

        int add(int quantity);

        int remove(int quantity);

        friend void inspect<game::Stack>(game::Stack &stack);
    };

} // namespace game

template <>
inline void inspect<game::Stack>(game::Stack &stack)
{
    ImGui::InputInt("quantity", &stack._quantity);
    ImGui::Text("name  : %s", stack._item.name().c_str());
}