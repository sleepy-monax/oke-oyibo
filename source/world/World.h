#pragma once

#include <entt.hpp>

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

        template <typename TSystem, typename... Args>
        void register_system(Args &&... args)
        {
            _systems.push_back(utils::own<TSystem>(std::forward<Args>(args)...));
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
