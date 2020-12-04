#include <cstdio>

#include "utils/Noise.h"

namespace utils
{
    uint8_t Noise::hash(int32_t i) const
    {
        return _perm[(uint8_t)(i)];
    }

    double Noise::grad(int32_t hash, double x, double y) const
    {
        // Convert low 3 bits of hash code
        const int32_t h = hash & 0x3F;

        // into 8 simple gradient directions,
        const double u = h < 4 ? x : y;
        const double v = h < 4 ? y : x;

        // and compute the dot product with (x,y).
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
    }

    inline int32_t Noise::fastfloor(float fp) const
    {
        int32_t i = (int32_t)(fp);
        return (fp < i) ? (i - 1) : (i);
    }

    double Noise::noise_pass(double x, double y, double scale) const
    {
        x *= scale;
        y *= scale;

        double n0, n1, n2; // Noise contributions from the three corners

        // Skewing/Unskewing factors for 2D
        static const double F2 = 0.366025403f; // F2 = (sqrt(3) - 1) / 2
        static const double G2 = 0.211324865f; // G2 = (3 - sqrt(3)) / 6   = F2 / (1 + 2 * K)

        // Skew the input space to determine which simplex cell we're in
        const double s = (x + y) * F2; // Hairy factor for 2D
        const double xs = x + s;
        const double ys = y + s;
        const int32_t i = fastfloor(xs);
        const int32_t j = fastfloor(ys);

        // Unskew the cell origin back to (x,y) space
        const double t = (double)(i + j) * G2;
        const double X0 = i - t;
        const double Y0 = j - t;
        const double x0 = x - X0; // The x,y distances from the cell origin
        const double y0 = y - Y0;

        int32_t i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
        if (x0 > y0)
        {
            i1 = 1;
            j1 = 0;
        }
        else
        {
            i1 = 0;
            j1 = 1;
        }

        const double x1 = x0 - i1 + G2;
        const double y1 = y0 - j1 + G2;
        const double x2 = x0 - 1.0f + 2.0f * G2;
        const double y2 = y0 - 1.0f + 2.0f * G2;

        const int gi0 = hash(i + hash(j));
        const int gi1 = hash(i + i1 + hash(j + j1));
        const int gi2 = hash(i + 1 + hash(j + 1));

        double t0 = 0.5f - x0 * x0 - y0 * y0;
        if (t0 < 0.0f)
        {
            n0 = 0.0f;
        }
        else
        {
            t0 *= t0;
            n0 = t0 * t0 * grad(gi0, x0, y0);
        }

        double t1 = 0.5f - x1 * x1 - y1 * y1;
        if (t1 < 0.0f)
        {
            n1 = 0.0f;
        }
        else
        {
            t1 *= t1;
            n1 = t1 * t1 * grad(gi1, x1, y1);
        }

        double t2 = 0.5f - x2 * x2 - y2 * y2;
        if (t2 < 0.0f)
        {
            n2 = 0.0f;
        }
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * grad(gi2, x2, y2);
        }

        return 45.23065f * (n0 + n1 + n2);
    }

    double Noise::noise(double x, double y) const
    {
        if (_octaves == 1)
        {
            return noise_pass(x, y, _scale);
        }
        else
        {
            double value = 0;
            double strength = 1;
            double normalizer = 0;
            double scale = _scale;

            for (int i = 0; i < _octaves; i++)
            {
                value += noise_pass(x, y, scale) * strength;
                normalizer += strength;
                strength /= 2;
                scale *= 2;
            }

            return value / normalizer;
        }
    }

} // namespace utils