#pragma once

#include <string>

#include "core/Texture.h"

namespace game
{
    class Item
    {
    private:
        std::string _name;
        core::Texture _texture;
        int _flags;

    public:
        static constexpr auto FOOD = 1 << 0;
        static constexpr auto SUPER_FOOD = 1 << 1;

        std::string name() const
        {
            return _name;
        }

        core::Texture texture() const
        {
            return _texture;
        }

        int flags() const
        {
            return _flags;
        }

        Item(std::string name, core::Texture texture, int flags = 0) :
            _name(name), _texture(texture), _flags(flags) {}

        bool operator==(const Item &other)
        {
            return name() == other.name();
        }
    };

} // namespace game
