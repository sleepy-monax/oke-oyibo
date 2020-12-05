#pragma once

#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

namespace game
{
    class HoldItemSystem : public core::System
    {
    private:
        core::Texture texture;

    public:
        HoldItemSystem();
        ~HoldItemSystem();

        void update(core::World &world, core::Time &time);
        void render(core::World &world, core::Camera &camera);
    };

} // namespace game
