#include "game/Registery.h"

#include "base/components/Acceleration.h"
#include "base/components/Colider.h"
#include "base/components/LightSource.h"
#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"
#include "base/components/Velocity.h"
#include "game/components/Armor.h"
#include "game/components/Flammable.h"
#include "game/components/Growable.h"
#include "game/components/Health.h"
#include "game/components/Hunger.h"
#include "game/components/Stamina.h"
#include "game/components/Pickable.h"
#include "game/components/Inventory.h"

#include "base/systems/Camera.h"
#include "base/systems/DebugRender.h"
#include "base/systems/EntityRenderer.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Physic.h"
#include "base/systems/TerrainRender.h"
#include "game/systems/HealthBar.h"
#include "game/systems/HungerSystem.h"
#include "game/systems/ThirstSystem.h"
#include "game/systems/StaminaSystem.h"
#include "game/systems/InventorySystem.h"
#include "game/systems/EnemyMove.h"

utils::RefPtr<core::Registry> game::make_registry()
{
    auto registry = utils::make<core::Registry>();

    registry->register_system<base::Input>("input");
    registry->register_system<base::DebugRender>("debug");
    registry->register_system<base::Physic>("physic");
    registry->register_system<base::TerrainRender>("terrain");
    registry->register_system<base::Light>("light");
    registry->register_system<base::Camera>("camera");
    registry->register_system<game::HealthBar>("health-bar");
    registry->register_system<game::HungerSystem>("hunger");
    registry->register_system<game::ThirstSystem>("thirst");
    registry->register_system<base::EntityRenderer>("entity");
    registry->register_system<game::StaminaSystem>("stamina");
    registry->register_system<game::InventorySystem>("inventory");
    registry->register_system<game::EnemyMove>("enemy");

    registry->register_component<base::Player>("player");
    registry->register_component<base::Position>("position");
    registry->register_component<base::Velocity>("velocity");
    registry->register_component<base::Acceleration>("acceleration");
    registry->register_component<base::LightSource>("light-source");
    registry->register_component<base::Sprite>("sprite");
    registry->register_component<game::Health>("health");
    registry->register_component<game::Hunger>("hunger");
    registry->register_component<game::Thirst>("thirst");
    registry->register_component<game::Stamina>("stamina");
    registry->register_component<game::Pickable>("pickable");
    registry->register_component<game::Inventory>("inventory");

    return registry;
}