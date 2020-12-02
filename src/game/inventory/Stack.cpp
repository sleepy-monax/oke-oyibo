#include "Stack.h"

namespace game
{
    Stack::Stack(Item item, int quantity): item(item), _quantity(quantity) {}

    Stack::~Stack() {}

    Item Stack::getItem() const {
        return item;
    }

    int Stack::getQuantity() const {
        return _quantity;
    }

    void Stack::set_quantity(int quantity) {
        _quantity = quantity;
    }

    int Stack::add(int quantity_add) {
        if (_quantity + quantity_add >= MAX_QUANTITY)
        {
            int rest = quantity_add + _quantity - MAX_QUANTITY;
            _quantity = MAX_QUANTITY;
            return rest;
        }
        else
        {
            _quantity += quantity_add;
            return 0;
        }        
    }
} // namespace game
