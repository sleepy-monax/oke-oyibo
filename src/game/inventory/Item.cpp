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

    core::Texture Item::get_texture() {
        return texture;
    }

} // namespace game
