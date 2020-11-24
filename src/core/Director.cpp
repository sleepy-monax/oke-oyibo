//
// Created by oslo on 11/23/20.
//
#include "core/Director.h"
#include <raylib.h>

namespace core
{
    Director::Director() {}

    Director::~Director()
    {
        delete _current;
    }

    Scene *Director::getCurrent() const
    {
        return _current;
    }

    void Director::setCurrent(Scene *current)
    {
        Director::_current = current;
    }

    void Director::switch_scene(Scene *scene)
    {
        setCurrent(scene);
    }

    void Director::run()
    {
        Time time{GetFrameTime(), GetTime()};

        _current->update(time);
        _current->render();
    }
} // namespace core
