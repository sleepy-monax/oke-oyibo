//
// Created by oslo on 11/23/20.
//
#include <raylib.h>

#include "core/BlankScene.h"
#include "core/Director.h"

namespace core
{
    Director::Director(utils::RefPtr<Registry> registry) :
        _current{utils::own<BlankScene>(*this, *registry)},
        _registry(registry)
    {
    }

    Scene &Director::current()
    {
        return *_current;
    }

    void Director::run()
    {
        Time time{GetFrameTime(), GetTime()};

        _current->update(time);
        _current->render();

        if (_next)
        {
            _current->on_switch_out();
            _current = _next;
            _current->on_switch_in();
        }
    }
} // namespace core
