#include "Item.h"

namespace game
{

    Item::Item(string name, core::Texture texture):
    name(name), texture(texture)
    {
    }
    
    Item::~Item()
    {
    }

    string Item::getName() {
        return name;
    }

} // namespace game
