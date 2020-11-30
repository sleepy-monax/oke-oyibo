#pragma once

#include "utils/Rect.h"

#include "core/Tile.h"

namespace core
{
    class Terrain
    {
    private:
        int _width;
        int _height;
        Tile *_tiles;

    public:
        utils::Recti bound() { return {_width * Tile::SIZE, _height * Tile::SIZE}; }

        int width() { return _width; }

        int height() { return _height; }

        Tile &tile(int x, int y) { return _tiles[y * _width + x]; }

        Terrain(int width, int height) :
            _width(width), _height(height)
        {
            _tiles = new Tile[width * height];
        }

        ~Terrain()
        {
            delete[] _tiles;
        }
    };
} // namespace core
