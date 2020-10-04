#pragma once

#include <functional>
#include <map>
#include <string>

#include "utils/OwnPtr.h"

#include "core/systems/System.h"
#include "editor/Inspect.h"

namespace core::world
{
    class World;
} // namespace core::world

namespace core
{
    struct SystemRegistryEntry
    {
        std::string name;
        std::function<void(core::world::World &, core::systems::System &)> inspect;
    };

    struct ComponentRegistryEntry
    {
        std::string name;
        std::function<void(core::world::World &, entt::entity)> inspect;
    };

    class Registry
    {
    private:
        std::map<entt::id_type, SystemRegistryEntry> _systems{};
        std::map<entt::id_type, ComponentRegistryEntry> _components{};

    public:
        Registry() {}

        ~Registry() {}

        template <typename TSystem>
        void register_system(const char *name)
        {
            auto id = entt::type_info<TSystem>::id();

            auto inspect_wrapper = [](core::world::World &w, core::systems::System &s) { inspect_system<TSystem>(w, sketchy_cast<core::systems::System, TSystem>(s)); };

            _systems.insert_or_assign(id, SystemRegistryEntry{name, inspect_wrapper});
        }

        template <typename TCallback>
        void foreach_system(TCallback callback)
        {
            for (auto &[id, info] : _systems)
            {
                callback(id, info);
            }
        }

        template <typename TComponent>
        void register_component(const char *name)
        {
            auto id = entt::type_info<TComponent>::id();

            auto inspect_wrapper = [](core::world::World &w, entt::entity e) { inspect_component<TComponent>(w, e); };

            _components.insert_or_assign(id, ComponentRegistryEntry{name, inspect_wrapper});
        }

        template <typename TCallback>
        void foreach_components(TCallback callback)
        {
            for (auto &[id, info] : _components)
            {
                callback(id, info);
            }
        }
    };
} // namespace core
