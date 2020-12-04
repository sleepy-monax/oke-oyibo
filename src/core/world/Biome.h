#pragma once

#include <string>
#include <utils/Vec.h>
#include <utils/Vector.h>

#include "utils/Noise.h"

#include "core/Blueprint.h"
#include "core/Tile.h"
#include "core/world/TEM.h"

namespace core
{
    struct Decoration
    {
        double precedence;
        utils::RefPtr<core::Blueprint> entity;
        double frequency;
        utils::Noise noise;
    };

    struct Biome
    {
        std::string name{"none"};
        core::Tile tile;
        TEM climat;
        //utils::Vector<Decoration> decorations;
    };
} // namespace core
