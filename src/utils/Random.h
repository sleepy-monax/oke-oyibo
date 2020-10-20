#pragma once

#include "utils/Common.h"

namespace utils
{
    typedef struct
    {
        uint64_t state;
        uint64_t inc;
    } Pcg32RandomState;

    uint32_t pcg32_random_r(Pcg32RandomState &rng)
    {
        uint64_t oldstate = rng.state;
        // Advance internal state
        rng.state = oldstate * 6364136223846793005ULL + (rng.inc | 1);
        // Calculate output function (XSH RR), uses old state for max ILP
        uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
        uint32_t rot = oldstate >> 59u;

        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }
} // namespace utils
