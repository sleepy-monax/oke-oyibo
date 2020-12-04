#pragma once

#include "utils/Common.h"

namespace utils
{
    class Random
    {
    private:
        uint64_t _state;
        uint64_t _inc;

    public:
        void seed(uint32_t seed)
        {
            _state = seed | (uint64_t)seed << 32;
            _inc = (seed | ((uint64_t)seed << 32)) ^ ((uint64_t)seed << 16);
        }

        Random()
        {
        }

        uint32_t next_u32()
        {
            uint64_t oldstate = _state;

            // Advance internal state
            _state = oldstate * 6364136223846793005ULL + (_inc | 1);

            // Calculate output function (XSH RR), uses old state for max ILP
            uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
            uint32_t rot = oldstate >> 59u;

            return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
        }

        double next_double()
        {
            return next_u32() / (double)UINT32_MAX;
        }
    };

} // namespace utils
