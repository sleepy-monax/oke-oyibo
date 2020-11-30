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
        utils::OwnPtr<Scene> _next = nullptr;
        utils::RefPtr<Registry> _registry;

    public:
        Director(utils::RefPtr<Registry> registry);

        Scene &current();

        template <typename TScene, typename... TArgs>
        void switch_scene(TArgs &&... args)
        {
            _next = utils::own<TScene>(*this, *_registry, std::forward<TArgs>(args)...);
        }

        void run();
    };
} // namespace core