//
// Created by oslo on 11/23/20.
//
#include <raylib.h>

#include "core/BlankScene.h"
#include "core/Director.h"

namespace core
{
    Director::Director(utils::RefPtr<Registry> registry) :
        _current{utils::own<BlankScene>()},
        _registry(registry)
    {
    }

    Scene &Director::current()
    {
        return *_current;
    }

    void Director::switch_scene(utils::OwnPtr<Scene> scene)
    {
        _current->on_switch_out();
        _current = scene;

        _current->director(*this);
        _current->registry(*_registry);

        _current->on_switch_in();
    }

    void Director::run()
    {
        Time time{GetFrameTime(), GetTime()};

        _current->update(time);
        _current->render();
    }
} // namespace core
