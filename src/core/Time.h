#pragma once

namespace core
{
    class Time
    {
    private:
        double _elapsed_time;
        double _total_time;

    public:
        double elapsed_time() { return _elapsed_time; }
        double total_time() { return _total_time; }

        Time(double elapsed_time, double total_time)
            : _elapsed_time(elapsed_time), _total_time(total_time)
        {
        }

        ~Time()
        {
        }
    };
} // namespace core
