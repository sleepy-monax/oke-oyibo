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
        Director *_director{nullptr};
        Registry *_registry{nullptr};

    public:
        Director &director()
        {
            assert(_director);
            return *_director;
        }

        Registry &registry()
        {
            assert(_registry);
            return *_registry;
        }

        void director(Director &director) { _director = &director; };

        void registry(Registry &registry) { _registry = &registry; };

        Scene()
        {
        }

        virtual ~Scene() {}

        virtual void update(Time &) {}

        virtual void render() {}

        virtual void on_switch_in() {}

        virtual void on_switch_out() {}
    };
} // namespace core
