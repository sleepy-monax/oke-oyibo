#pragma once

#include <functional>
#include <string>

#include "utils/HashMap.h"
#include "utils/OwnPtr.h"

#include "base/components/Component.h"
#include "core/System.h"

namespace core
{
    class World;
} // namespace core

namespace core
{
    struct SystemRegistryEntry
    {
        std::string name;
        std::function<void(core::World &, core::System &)> inspect;
    };

    struct ComponentRegistryEntry
    {
        std::string name;
        std::function<void(core::World &, entt::entity)> inspect;
    };

    class Registry
    {
    private:
        utils::HashMap<entt::id_type, SystemRegistryEntry> _systems{};
        utils::HashMap<entt::id_type, ComponentRegistryEntry> _components{};

    public:
        Registry() {}

        ~Registry() {}

        template <typename TSystem>
        void register_system(const char *name)
        {
            auto id = entt::type_info<TSystem>::id();

            auto inspect_wrapper = [](core::World &w, core::System &s) { inspect_system<TSystem>(w, sketchy_cast<core::System, TSystem>(s)); };

            _systems[id] = SystemRegistryEntry{name, inspect_wrapper};
        }

        template <typename TCallback>
        void foreach_system(TCallback callback)
        {
            _systems.foreach (callback);
        }

        SystemRegistryEntry &system_info(entt::id_type id)
        {
            return _systems[id];
        }

        template <typename TComponent>
        void register_component(const char *name)
        {
            auto id = entt::type_info<TComponent>::id();

            auto inspect_wrapper = [](core::World &w, entt::entity e) { inspect_component<TComponent>(w, e); };

            _components[id] = ComponentRegistryEntry{name, inspect_wrapper};
        }

        template <typename TCallback>
        void foreach_components(TCallback callback)
        {
            _components.foreach (callback);
        }
    };
} // namespace core
