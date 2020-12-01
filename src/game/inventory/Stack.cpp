#include "Stack.h"

namespace game
{
    Stack::Stack(Item item, int quantity): item(item), quantity(quantity) {}

    Stack::~Stack() {}

    Item Stack::getItem() const {
        return item;
    }

    int Stack::getQuantity() const {
        return quantity;
    }

    void Stack::add(int quantity_add) {
        if (quantity + quantity_add > MAX_QUANTITY)
        {
            quantity = MAX_QUANTITY;
        }
        else
        {
            quantity += quantity_add;
        }        
    }
} // namespace game
