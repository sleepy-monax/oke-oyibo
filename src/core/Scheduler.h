#include <core/Time.h>
#include <utils/Callback.h>
#include <utils/Vector.h>

namespace core
{

    class Scheduler
    {
    private:
        struct Action
        {
            double timepoint;
            utils::Callback<void()> callback;
        };

        double _time;
        utils::Vector<Action> _actions;

    public:
        Scheduler() {}

        void update(Time &time)
        {
            _time += time.elapsed();

            for (size_t i = 0; i < _actions.count(); i++)
            {
                while (i < _actions.count() && _actions[i].timepoint < _time)
                {
                    _actions[i].callback();
                    _actions.remove_index(i);
                }
            }
        }

        void schedule(double time, utils::Callback<void()> callback)
        {
            _actions.push_back({time, callback});
        }
    };
} // namespace core
