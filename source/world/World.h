#pragma once

#include <entt.hpp>

#include "entity/Builder.h"
#include "game/RenderContext.h"
#include "game/UpdateContext.h"
#include "systems/System.h"
#include "utils/OwnPtr.h"
#include "utils/Vector.h"
#include "world/Terrain.h"

namespace world
{
    class World
    {
    private:
        Terrain _terrain;
        entt::registry _entities;
        utils::Vector<utils::OwnPtr<systems::System>> _systems;

    public:
        Terrain &terrain()
        {
            return _terrain;
        }

        entt::registry &entities()
        {
            return _entities;
        }

        World(int width, int height)
            : _terrain{width, height},
              _entities{},
              _systems{}
        {
        }

        ~World() {}

        template <typename TSystem, typename... TArgs>
        void register_system(TArgs &&... args)
        {
            _systems.push_back(utils::own<TSystem>(std::forward<TArgs>(args)...));
        }

        entity::Builder create_entity()
        {
            return entity::Builder{entities()};
        }

        void update(game::UpdateContext &context)
        {
            _systems.foreach ([&](auto &sys) {
                sys->do_update(*this, context);
                return utils::Iteration::CONTINUE;
            });
        }

        void render(game::RenderContext &context)
        {
            _systems.foreach ([&](auto &sys) {
                sys->do_render(*this, context);
                return utils::Iteration::CONTINUE;
            });
        }

        void display()
        {
            _systems.foreach ([&](auto &sys) {
                sys->do_display(*this);
                return utils::Iteration::CONTINUE;
            });
        }
    };
} // namespace world
