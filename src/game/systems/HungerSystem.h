#pragma once

#include "core/Registry.h"
#include "core/Graphics.h"
#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

#include "game/components/Health.h"
#include "game/components/Hunger.h"
#include "game/components/Stamina.h"

#include "base/components/Position.h"

namespace game
{
    class HungerSystem: public core::System
    {
    private:
        double _accumulator = 0;
        core::Texture foodTexture;

    public:
        HungerSystem();

        void update(core::World &world, core::Time &time);

        bool stackFrame(core::Time &time);

        void on_load(core::Registry &registry) override;

        void render(core::World &world, core::Camera &camera);

        friend void inspect<game::HungerSystem>(game::HungerSystem &hungerSystem);
    };
} // namespace game

template <>
inline void inspect<game::HungerSystem>(game::HungerSystem &hungerSystem)
{
    ImGui::InputDouble("accumulator##HungerSystem", &hungerSystem._accumulator);
}