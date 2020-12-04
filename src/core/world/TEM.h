#pragma once

#include <cmath>

namespace core
{

    class TEM
    {
    private:
        double _temperature;
        double _elevation;
        double _moisture;

    public:
        double temperature() { return _temperature; };
        double elevation() { return _elevation; };
        double moisture() { return _moisture; };

        TEM() :
            _temperature{0},
            _elevation{0},
            _moisture{0}
        {
        }

        TEM(double temperature, double elevation, double moisture) :
            _temperature{temperature},
            _elevation{elevation},
            _moisture{moisture}
        {
        }

        double difference(const TEM &other)
        {
            return sqrt(
                (_temperature - other._temperature) * (_temperature - other._temperature) +
                (_elevation - other._elevation) * (_elevation - other._elevation) +
                (_moisture - other._moisture) * (_moisture - other._moisture));
        }
    };

} // namespace core
