#pragma once

namespace core
{
    class Time
    {
    private:
        double _elapsed;
        double _total;

    public:
        double elapsed() { return _elapsed; }
        double total() { return _total; }

        Time(double elapsed, double total) :
            _elapsed(elapsed),
            _total(total)
        {
        }
    };
} // namespace core
