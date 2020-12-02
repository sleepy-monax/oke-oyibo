#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>

#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"

#include "game/inventory/Item.h"
#include "game/inventory/Stack.h"

#include "core/Camera.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"
#include "core/Registry.h"

#include "editor/panels/Entities.h"
#include "editor/panels/Inspector.h"
#include "editor/panels/Profiler.h"
#include "editor/panels/Systems.h"
#include "editor/panels/Viewport.h"

using namespace std;

namespace game
{
    class Generator
    {
    private :
        float randomX;
        float randomY;
        vector<string> enemy_sprites;
        vector<string> food_sprites;
        utils::RefPtr<core::World> world;
        base::Position position;

    public :
        Generator();
        ~Generator();

        void create_enemy_sprite(); 
        void create_food_sprite();
        void generate_world();
        void generate_enemy(core::World &world, core::Registry &reg);
        void generate_food(core::World &world, core::Registry &reg);

    };
} // namespace game