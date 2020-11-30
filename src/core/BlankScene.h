#pragma once

#include "core/Scene.h"

namespace core
{
    class BlankScene: public Scene
    {
    public:
        BlankScene(Director &dir, Registry &reg) :
            Scene(dir, reg) {}
    };
} // namespace core
