//
// Created by oslo on 11/23/20.
//
#include <raylib.h>

#include "core/BlankScene.h"
#include "core/Director.h"

namespace core
{
    Director::Director() :
        _current{utils::own<BlankScene>()}
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
        _current->on_switch_in();
    }

    void Director::run()
    {
        Time time{GetFrameTime(), GetTime()};

        _current->update(time);
        _current->render();
    }
} // namespace core
