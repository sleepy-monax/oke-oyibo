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
    class Decoration
    {
    private:
        double _precedence;
        utils::RefPtr<core::Blueprint> _entity = nullptr;
        double _frequency;
        utils::Noise _noise;

    public:
        double precedence() const { return _precedence; }

        utils::RefPtr<core::Blueprint> entity() const { return _entity; }

        double frequency() const { return _frequency; }

        const utils::Noise &noise() const { return _noise; }

        Decoration(
            double precedence,
            utils::RefPtr<core::Blueprint> entity,
            double frequency,
            utils::Noise noise) :

            _precedence(precedence),
            _entity(entity),
            _frequency(frequency),
            _noise(noise)
        {
        }
    };

    struct Biome
    {
        std::string name{"none"};
        core::Tile tile;
        TEM climat;

        utils::Vector<Decoration> decorations;

        double total_precedence()
        {
            double total = 0;

            for (size_t i = 0; i < decorations.count(); i++)
            {
                total += decorations[i].precedence();
            }

            return total;
        }

        Decoration &pick_by_precedence(double precedence)
        {
            for (size_t i = 0; i < decorations.count(); i++)
            {
                if (precedence < decorations[i].precedence())
                {
                    return decorations[i];
                }

                precedence -= decorations[i].precedence();
            }

            assert(false);
        }
    };
} // namespace core
