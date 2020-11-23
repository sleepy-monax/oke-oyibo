//
// Created by oslo on 11/23/20.
//
#pragma once

#include "core/Time.h"

namespace core
{

    class Scene
    {
    public:
        Scene() {}
        virtual ~Scene() {}

        virtual void update(Time &) {}
        virtual void render() {}
        virtual void on_switch_in() {}
        virtual void on_switch_out() {}
    };

} // namespace core
