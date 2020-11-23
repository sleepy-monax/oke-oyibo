//
// Created by oslo on 11/23/20.
//
#pragma once

#include "core/Scene.h"

namespace core
{
    class Director {

    private:
        Scene *_current;

    public:
        Director();
        virtual ~Director();

        Scene *getCurrent() const;
        void setCurrent(Scene *current);

        void switch_scene(Scene *scene);
        void run();

    };
}