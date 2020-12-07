#include "core/World.h"
#include "core/Registry.h"

namespace core
{

    World::World(utils::RefPtr<Registry> registry, int width, int height) :
        _registry(registry),
        _terrain{width, height},
        _entities{},
        _systems{}
    {
        registry->foreach_system([&](auto &key, auto &value) {
            auto sys = value.create();
            sys->on_load(*registry);
            _systems[key] = sys;

            return utils::Iteration::CONTINUE;
        });
    }

    void World::add_player(core::Player &&player)
    {
        _players.push_back(std::move(player));
    }

    Builder World::create_entity()
    {
        return Builder{entities()};
    }

    void World::update(Time &time)
    {
        _systems.foreach ([&](auto &, auto &sys) {
            sys->do_update(*this, time);
            return utils::Iteration::CONTINUE;
        });

        for (size_t i = 0; i < _entities_removed.count(); i++)
        {
            if (_entities.valid(_entities_removed[i]))
            {
                _entities.destroy(_entities_removed[i]);
            }
        }

        _entities_removed.clear();
    }

    void World::render(Camera &camera)
    {
        _systems.foreach ([&](auto &, auto &sys) {
            sys->do_render(*this, camera);
            return utils::Iteration::CONTINUE;
        });
    }

} // namespace core
