#pragma once

#include <cstdlib>

#include "utils/Common.h"
#include "utils/Vec.h"

namespace utils
{
    class Noise
    {
    private:
        uint32_t _seed = 0;
        int _octaves = 1;
        double _scale = 1;

        uint8_t _perm[256] = {
            151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
            36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
            234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
            88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
            134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
            230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
            1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
            116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
            124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
            47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44,
            154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
            108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
            242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
            239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121,
            50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243,
            141, 128, 195, 78, 66, 215, 61, 156, 180};

        uint8_t hash(int32_t i) const;

        double grad(int32_t hash, double x, double y) const;

        int32_t fastfloor(float fp) const;

        double noise_pass(double x, double y, double scale) const;

    public:
        void seed(uint32_t seed)
        {
            seed ^= _seed;

            for (size_t i = 0; i < 256; i++)
            {
                _perm[i] = i;
            }

            srand(seed);

            for (size_t i = 0; i < 512; i++)
            {
                int a = rand() % 256;
                int b = rand() % 256;

                auto t = _perm[a];
                _perm[a] = _perm[b];
                _perm[b] = t;
            }
        }

        Noise(uint32_t seed, int octaves, double scale) :
            _seed(seed), _octaves(octaves), _scale(scale)
        {
        }

        double noise(Vec2f pos) const { return noise(pos.x(), pos.y()); }

        double noise(double x, double y) const;
    };

} // namespace utils
