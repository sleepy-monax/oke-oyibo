#include "HoldItemSystem.h"

#include <string>

#include "raylib.h"

#include "base/components/Player.h"
#include "game/components/HoldItem.h"
#include "game/components/Inventory.h"

#include "core/Graphics.h"
#include "core/Registry.h"
#include "core/Scene.h"

namespace game
{
    HoldItemSystem::HoldItemSystem()
    {
    }

    HoldItemSystem::~HoldItemSystem()
    {
    }

    void HoldItemSystem::update(core::World &world, core::Time &)
    {
        auto player = world.entities().view<game::Inventory, game::HoldItem, base::Player>();

        player.each([&](auto &inventory, auto &hold, auto &) {
            if (IsKeyPressed(KEY_SPACE))
            {
                if (inventory.inventory.count())
                {
                    hold.index = (hold.index + 1) % inventory.inventory.count();
                }
            }
        });
    }

    void HoldItemSystem::on_load(core::Registry &registry)
    {
        font = registry.font("romulus");
    }

    void HoldItemSystem::render(core::World &world, core::Camera &camera)
    {
        auto player = world.entities().view<game::Inventory, game::HoldItem, base::Position>();

        camera.with_entities([&]() {
            player.each([&](auto &inv, auto &hold, auto &position) {
                utils::Rectf bound = {2, -11, 8, 8};

                bound = bound.offset(position());

                if (inv.inventory.count() > 0)
                {
                    if (hold.index < inv.inventory.count())
                    {
                        auto texture = inv.inventory[hold.index].item().texture();
                        auto num = inv.inventory[hold.index].quantity();

                        Vector2 pos(position().x() + 6, position().y() - 6);
                        core::draw_texture(texture, bound, WHITE);
                        DrawTextEx(font, std::to_string(num).c_str(), pos, 5.f, 1.f, WHITE);
                    }
                }
            });
        });
    }

}; // namespace game
