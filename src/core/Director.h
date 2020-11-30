//
// Created by oslo on 11/23/20.
//
#pragma once

#include "core/Scene.h"

#include "utils/OwnPtr.h"

namespace core
{
    class Director
    {
    private:
        utils::OwnPtr<Scene> _current;

    public:
        Director();

        Scene &current();

        void switch_scene(utils::OwnPtr<Scene> scene);

        void run();
    };
} // namespace core