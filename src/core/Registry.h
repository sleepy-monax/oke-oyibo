#pragma once

#include <functional>
#include <string>

#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/RefCounter.h"

#include "base/components/Component.h"
#include "core/System.h"

namespace core
{
    class World;
} // namespace core

namespace core
{
    struct SystemDescription
    {
        std::string name;

        std::function<void(core::World &, core::System &)> inspect;
        std::function<utils::OwnPtr<core::System>()> create;
    };

    struct ComponentDescription
    {
        std::string name;

        std::function<void(core::World &, entt::entity)> inspect;
    };

    class Registry: public utils::RefCounted<Registry>
    {
    private:
        utils::HashMap<entt::id_type, SystemDescription> _systems{};
        utils::HashMap<entt::id_type, ComponentDescription> _components{};

    public:
        Registry() {}

        template <typename TSystem>
        void register_system(const char *name)
        {
            auto id = entt::type_info<TSystem>::id();

            auto inspect_wrapper = [](core::World &w, core::System &s) {
                inspect_system<TSystem>(w, sketchy_cast<core::System, TSystem>(s));
            };

            auto create_wrapper = []() {
                return utils::own<TSystem>();
            };

            _systems[id] = SystemDescription{
                name,
                inspect_wrapper,
                create_wrapper,
            };
        }

        template <typename TCallback>
        void foreach_system(TCallback callback)
        {
            _systems.foreach (callback);
        }

        SystemDescription &system_info(entt::id_type id)
        {
            return _systems[id];
        }

        template <typename TComponent>
        void register_component(const char *name)
        {
            auto id = entt::type_info<TComponent>::id();

            auto inspect_wrapper = [](core::World &w, entt::entity e) {
                inspect_component<TComponent>(w, e);
            };

            _components[id] = ComponentDescription{name, inspect_wrapper};
        }

        template <typename TCallback>
        void foreach_components(TCallback callback)
        {
            _components.foreach (callback);
        }
    };
} // namespace core
