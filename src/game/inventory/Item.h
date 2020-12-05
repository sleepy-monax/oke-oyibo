#pragma once

#include <string>
#include "core/Texture.h"

using std::string;

namespace game
{
    class Item
    {
    private:
        string name;
        core::Texture texture;
        
    public:
        Item(string name, core::Texture texture);
        ~Item();

        string getName();

        core::Texture get_texture();
    };

} // namespace game
