//
// Created by oslo on 11/23/20.
//
#pragma once

#include <cassert>

#include "core/Time.h"

namespace core
{
    class Director;
    class Registry;

    struct Scene
    {
    private:
        Director &_director;
        Registry &_registry;

    public:
        Director &director()
        {
            return _director;
        }

        Registry &registry()
        {
            return _registry;
        }

        Scene(Director &director, Registry &registry) :
            _director(director), _registry(registry)
        {
        }

        virtual ~Scene() {}

        virtual void update(Time &) {}

        virtual void render() {}

        virtual void on_switch_in() {}

        virtual void on_switch_out() {}
    };
} // namespace core
