#pragma once

#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>

#include "utils/Macros.h"
#include "utils/OwnPtr.h"
#include "utils/Vector.h"

#include "core/world/Biome.h"
#include "core/world/Climat.h"

namespace game
{
    class Generator
    {
    private:
        core::Climat _climat{};

    public:
        Generator()
        {
        }

        void generate_biomes(core::Registry &reg, core::World &world)
        {
            auto island = [&](float x, float y) {
                // ((((sin(x * PI) + sin(y * PI)) / 2) ^ 2) - 0.5) * 2;

                double x_island = sin(x / world.terrain().width() * PI);
                double y_island = sin(y / world.terrain().height() * PI);

                double product = (x_island + y_island) / 2;

                double cube = product * product;

                return (cube - 0.5) * 2;
            };

            for (float y = 0; y < world.terrain().height(); y += 1.0)
            {
                for (float x = 0; x < world.terrain().width(); x += 1.0)
                {
                    core::TEM tem = _climat.sample({x, y});

                    core::TEM new_tem = {
                        tem.temperature(),
                        (tem.elevation() + island(x, y) * 2) / 3,
                        tem.moisture(),
                    };

                    auto &biome = reg.lookup_biome(new_tem);
                    world.terrain().tile((int)x, (int)y) = biome.tile;
                }
            }
        }

        utils::RefPtr<core::World> generate(core::Registry &reg, uint32_t seed)
        {
            _climat.seed(seed);

            auto world = utils::make<core::World>(reg, 256, 256);

            generate_biomes(reg, *world);

            return world;
        }
    };
} // namespace game