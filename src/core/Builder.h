#pragma once

#include <entt/entity/registry.hpp>

namespace core
{
    class Builder
    {
    private:
        entt::registry &_registry;
        entt::entity _entity;

    public:
        Builder(entt::registry &registry) :
            _registry(registry), _entity(registry.create())
        {
        }

        template <typename TComponent, typename... TArgs>
        Builder &with(TArgs &&... args)
        {
            _registry.emplace_or_replace<TComponent>(_entity, std::forward<TArgs>(args)...);
            return *this;
        }

        template <typename TComponent>
        Builder &with(TComponent component)
        {
            _registry.emplace_or_replace<TComponent>(_entity, component);
            return *this;
        }
    };
} // namespace core
