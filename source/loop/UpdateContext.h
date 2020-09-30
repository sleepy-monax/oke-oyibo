#pragma once

namespace loop
{
    class UpdateContext
    {
    private:
        double _elapsed_time;
        double _total_time;

    public:
        double elapsed_time() { return _elapsed_time; }
        double total_time() { return _total_time; }

        UpdateContext(double elapsed_time, double total_time)
            : _elapsed_time(elapsed_time), _total_time(total_time)
        {
        }

        ~UpdateContext()
        {
        }
    };
} // namespace loop
