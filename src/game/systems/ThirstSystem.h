#pragma once

#include "core/Registry.h"
#include "core/Graphics.h"
#include "core/System.h"
#include "core/Time.h"
#include "core/World.h"

#include "game/components/Health.h"
#include "game/components/Thirst.h"

namespace game
{
    class ThirstSystem: public core::System
    {
    private:
        double _accumulator = 0;
        core::Texture waterTexture;

    public:
        ThirstSystem();

        ~ThirstSystem();

        void update(core::World &world, core::Time &time);

        bool stackFrame(core::Time &time);

        void on_load(core::Registry &registry) override ;

        void render(core::World &world, core::Camera &camera);

        friend void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem);
    };
} // namespace game

template <>
inline void inspect<game::ThirstSystem>(game::ThirstSystem &thirstSystem)
{
    ImGui::InputDouble("accumulator##ThirstSystem", &thirstSystem._accumulator);
}