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

        template <typename TScene, typename... TArgs>
        void switch_scene(TArgs &&...args)
        {
            _current->on_switch_out();
            _current = utils::own<TScene>(*this, *_registry, std::forward<TArgs>(args)...);
            _current->on_switch_in();
        }

        void run();
    };
} // namespace core