#pragma once

#include "utils/OwnPtr.h"
#include "utils/Vector.h"

#include "game/generator/Pass.h"

namespace game
{
    class Generator
    {
    private:
        utils::Vector<utils::OwnPtr<Pass>> _passes;

    public:
        template <typename TPass, typename... TArgs>
        TPass &add_pass(TArgs &&... args)
        {
            return _passes.push_back(utils::own<TPass>(std::forward<TArgs>(args)...));
        }

        utils::RefPtr<core::World> generate(uint32_t seed)
        {
            auto world = utils::make<core::World>(registry(), 256, 256);

            _passes.foreach ([&](auto &pass) {
                pass->apply(*world);
            });

            return world;
        }
    };
} // namespace game