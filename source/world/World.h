#pragma once

#include <entt.hpp>

#include "entity/Builder.h"
#include "loop/RenderContext.h"
#include "loop/UpdateContext.h"
#include "systems/System.h"
#include "utils/OwnPtr.h"
#include "utils/Vector.h"

namespace world
{
    class World
    {
    private:
        entt::registry _entities{};
        utils::Vector<utils::OwnPtr<systems::System>> _systems{};

    public:
        entt::registry &entities()
        {
            return _entities;
        }

        World()
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

        void update(loop::UpdateContext &context)
        {
            _systems.foreach ([&](auto &sys) {
                sys->do_update(*this, context);
                return utils::Iteration::CONTINUE;
            });
        }

        void render(loop::RenderContext &context)
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
