//
// Created by oslo on 11/23/20.
//
#pragma once

#include "core/Registry.h"
#include "core/Scene.h"

#include "utils/OwnPtr.h"

namespace core
{
    class Director
    {
    private:
        utils::OwnPtr<Scene> _current;
        utils::RefPtr<Registry> _registry;

    public:
        Director(utils::RefPtr<Registry> registry);

        Scene &current();

        void switch_scene(utils::OwnPtr<Scene> scene);

        void run();
    };
} // namespace core