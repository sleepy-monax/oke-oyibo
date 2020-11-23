//
// Created by oslo on 11/23/20.
//
#include "Director.h"

namespace core
{
    Director::Director() {}

    Director::~Director() {
        delete _current;
    }

    Scene *Director::getCurrent() const {
        return _current;
    }

    void Director::setCurrent(Scene *current) {
        Director::_current = current;
    }

    void Director::switch_scene(Scene *scene) {
        setCurrent(scene);
    }

    void Director::run() {
        Time time(12,12);
        _current->update(time);
        _current->render();
    }
}
