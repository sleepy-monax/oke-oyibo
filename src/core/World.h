#pragma once

#include <entt.hpp>

#include "core/Player.h"
#include "core/System.h"
#include "core/Time.h"
#include "core/entity/Builder.h"
#include "core/world/Terrain.h"
#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/Vector.h"

namespace core
{
    class Registry;
} // namespace core

namespace core
{
    class World
    {
    private:
        Registry &_registry;
        Terrain _terrain;
        entt::registry _entities;
        utils::HashMap<entt::id_type, utils::OwnPtr<System>> _systems;
        utils::Vector<core::Player> _players;

    public:
        auto &terrain() { return _terrain; }

        auto &entities() { return _entities; }

        auto &registry() { return _registry; }

        auto &systems() { return _systems; }

        auto &players() { return _players; }

        World(Registry &registry, int width, int height)
            : _registry(registry),
              _terrain{width, height},
              _entities{},
              _systems{}
        {
        }

        template <typename TSystem, typename... TArgs>
        void register_system(TArgs &&... args)
        {
            _systems[entt::type_info<TSystem>::id()] = utils::own<TSystem>(std::forward<TArgs>(args)...);
        }

        void add_player(core::Player &&player)
        {
            _players.push_back(std::move(player));
        }

        entity::Builder create_entity()
        {
            return entity::Builder{entities()};
        }

        void update(Time &context)
        {
            _systems.foreach ([&](auto &, auto &sys) {
                sys->do_update(*this, context);
                return utils::Iteration::CONTINUE;
            });
        }

        void render(Camera &context)
        {
            _systems.foreach ([&](auto &, auto &sys) {
                sys->do_render(*this, context);
                return utils::Iteration::CONTINUE;
            });
        }
    };
} // namespace core
