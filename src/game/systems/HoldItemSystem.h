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
        int num;
        Font font;

    public:
        HoldItemSystem();
        ~HoldItemSystem();

        void update(core::World &world, core::Time &time);
        void render(core::World &world, core::Camera &camera);
        void on_load(core::Registry &registry);
    };

} // namespace game
