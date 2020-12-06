#pragma once

#include <raylib.h>

#include "utils/Random.h"

#include "core/System.h"
#include "core/World.h"

#include "base/components/Player.h"
#include "base/components/Position.h"

#include "game/components/Health.h"

namespace game
{
    class HealthBar: public core::System
    {
    private:
        core::Texture healthTexture;
        utils::Random _random{};

    public:
        HealthBar();

        void on_load(core::Registry &registry) override;
        void update(core::World &world, core::Time &time) override;
        void render(core::World &world, core::Camera &camera) override;
    };
} // namespace game
