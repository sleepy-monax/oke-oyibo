#pragma once

#include <entt/entity/registry.hpp>

#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/RefPtr.h"
#include "utils/Vector.h"

#include "core/Blueprint.h"
#include "core/Builder.h"
#include "core/Player.h"
#include "core/System.h"
#include "core/Terrain.h"
#include "core/Time.h"

#include "base/components/CastShadow.h"
#include "base/components/Sprite.h"
#include "game/components/Pickable.h"
#include "game/inventory/Stack.h"

#include "base/components/Position.h"

namespace core
{
    class Registry;

    class World: public utils::RefCounted<World>
    {
    private:
        utils::RefPtr<Registry> _registry;
        Terrain _terrain;

        entt::registry _entities;
        utils::Vector<entt::entity> _entities_removed;

        utils::HashMap<entt::id_type, utils::OwnPtr<System>> _systems;
        utils::Vector<core::Player> _players;
        int _difficulty = 0;

        bool _win=false;

    public:
        auto &terrain() { return _terrain; }

        auto &entities() { return _entities; }

        auto &registry() { return *_registry; }

        auto &systems() { return _systems; }

        auto &players() { return _players; }

        int getDifficulty() { return _difficulty; }

        void setDifficulty(int newDifficulty) { 
            _difficulty = newDifficulty;
        }

        World(utils::RefPtr<Registry> registry, int width, int height);

        void add_player(core::Player &&);

        Builder create_entity();

        Builder create_entity(Blueprint &blueprint)
        {
            auto b = create_entity();
            blueprint.create(b);
            return b;
        }

        Builder create_entity(Blueprint &blueprint, utils::Vec2f position)
        {
            return create_entity(blueprint).with<base::Position>(position.x(), position.y(), 0.0f);
        }

        Builder create_item(game::Stack stack, utils::Vec2f position)
        {
            return create_entity()
                .with<base::Position>(position.x(), position.y(), 0.0f)
                .with<game::Pickable>(stack)
                .with<base::Sprite>(stack.item().texture())
                .with<base::CastShadow>(2, utils::Vec2f::zero());
        }

        void remove_entity(entt::entity entity)
        {
            _entities_removed.push_back(entity);
        }

        void update(Time &);

        void render(Camera &);

        bool isWin(){
            return _win;
        }

        void setWin(bool win){
            _win = win;
        }
    };
} // namespace core
