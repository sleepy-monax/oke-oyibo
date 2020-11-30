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
    }
} // namespace core
