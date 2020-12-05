#pragma once

#include "utils/Noise.h"

#include "core/world/TEM.h"

namespace core
{
    class Climat
    {
    private:
        utils::Noise _temperature{0xe7263ffb, 16, 1 / 256.};
        utils::Noise _elevation{0xfe9555c0, 32, 1 / 128.};
        utils::Noise _moisture{0x33d3de7b, 8, 1 / 256.};

    public:
        void seed(uint32_t seed)
        {
            _temperature.seed(seed);
            _elevation.seed(seed);
            _moisture.seed(seed);
        }

        TEM sample(utils::Vec2f pos)
        {
            return {
                _temperature.noise(pos),
                _elevation.noise(pos),
                _moisture.noise(pos),
            };
        }
    };
} // namespace core
