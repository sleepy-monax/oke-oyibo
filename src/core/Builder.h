#pragma once

#include <entt.hpp>

namespace core::entity
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
        Builder &with(TArgs &&...args)
        {
            _registry.emplace<TComponent>(_entity, std::forward<TArgs>(args)...);
            return *this;
        }
    };
} // namespace core::entity
