#include "game/Registry.h"

#include "base/components/CastShadow.h"
#include "base/components/Colider.h"
#include "base/components/LightSource.h"
#include "base/components/Momentum.h"
#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"

#include "game/components/Armor.h"
#include "game/components/Attack.h"
#include "game/components/Breakable.h"
#include "game/components/Enemy.h"
#include "game/components/Flammable.h"
#include "game/components/Growable.h"
#include "game/components/Health.h"
#include "game/components/HoldItem.h"
#include "game/components/Hunger.h"
#include "game/components/Inventory.h"
#include "game/components/Pickable.h"
#include "game/components/Stamina.h"

#include "base/systems/Camera.h"
#include "base/systems/EntityRenderer.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Movement.h"
#include "base/systems/Physic.h"
#include "base/systems/Shadow.h"
#include "base/systems/TerrainRender.h"

#include "game/systems/AttackSystem.h"
#include "game/systems/BreakableSystem.h"
#include "game/systems/EnemyMove.h"
#include "game/systems/HealthBar.h"
#include "game/systems/HoldItemSystem.h"
#include "game/systems/HungerSystem.h"
#include "game/systems/InventorySystem.h"
#include "game/systems/RegenSystem.h"
#include "game/systems/ReviveSystem.h"
#include "game/systems/StaminaSystem.h"
#include "game/systems/ThirstSystem.h"

utils::RefPtr<core::Registry> game::make_registry()
{
    utils::RefPtr<core::Registry> registry = utils::make<core::Registry>();

    registry->register_system<base::Camera>("camera");
    registry->register_system<base::EntityRenderer>("entity");
    registry->register_system<base::Input>("input");
    registry->register_system<base::Light>("light");
    registry->register_system<base::Shadow>("shadow");
    registry->register_system<base::Physic>("physic");
    registry->register_system<base::TerrainRender>("terrain");
    registry->register_system<base::Movement>("movement");

    registry->register_system<game::BreakableSystem>("breakable");
    registry->register_system<game::EnemyMove>("enemy-move");
    registry->register_system<game::HealthBar>("health-bar");
    registry->register_system<game::HungerSystem>("hunger");
    registry->register_system<game::InventorySystem>("inventory");
    registry->register_system<game::ReviveSystem>("revive");
    registry->register_system<game::StaminaSystem>("stamina");
    registry->register_system<game::ThirstSystem>("thirst");
    registry->register_system<game::RegenSystem>("regen");
    registry->register_system<game::HoldItemSystem>("hold-item");
    registry->register_system<game::AttackSystem>("attack");

    registry->register_component<base::Momentum>("momentum");
    registry->register_component<base::LightSource>("light-source");
    registry->register_component<base::Player>("player");
    registry->register_component<base::Position>("position");
    registry->register_component<base::Sprite>("sprite");
    registry->register_component<base::Move>("move");

    registry->register_component<game::Enemy>("enemy");
    registry->register_component<game::Health>("health");
    registry->register_component<game::Hunger>("hunger");
    registry->register_component<game::Inventory>("inventory");
    registry->register_component<game::Breakable>("breakable");
    registry->register_component<game::Pickable>("pickable");
    registry->register_component<game::Stamina>("stamina");
    registry->register_component<game::Thirst>("thirst");
    registry->register_component<game::HoldItem>("hold-item");
    registry->register_component<game::Attack>("attack");

    auto HEDGEHOG = registry->register_blueprint("hedgehog", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("hedgehog"));
        e.with<base::CastShadow>(4, utils::Vec2f{-1, 0});

        e.with<game::Health>(7, 7);
        e.with<game::Attack>(1);
    });

    auto BUNNY = registry->register_blueprint("bunny", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("bunny"));
        e.with<base::CastShadow>(4, utils::Vec2f{-1, 0});

        e.with<game::Health>(7, 7);
        e.with<game::Attack>(1);
    });

    auto ZOMBIE = registry->register_blueprint("zombie", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("zombie"));
        e.with<base::CastShadow>(4, utils::Vec2f{0.5, 0});

        e.with<game::Enemy>();
        e.with<game::Health>(7, 7);
        e.with<game::Attack>(1);
    });

    auto SKELETON = registry->register_blueprint("skeleton", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("skeleton"));
        e.with<base::CastShadow>(4, utils::Vec2f{0.5, 0});

        e.with<game::Enemy>();
        e.with<game::Health>(6, 6);
        e.with<game::Attack>(1);
    });

    auto SLIME = registry->register_blueprint("slime", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("slime"));
        e.with<base::CastShadow>(8, utils::Vec2f{0, 0});

        e.with<game::Enemy>();
        e.with<game::Health>(3, 3);
        e.with<game::Attack>(1);
    });

    auto BIG_SLIME = registry->register_blueprint("big-slime", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("big-slime"));
        e.with<base::CastShadow>(12, utils::Vec2f{0, 0});

        e.with<game::Enemy>();
        e.with<game::Health>(5, 5);
        e.with<game::Attack>(1);
    });

    auto WISP = registry->register_blueprint("wisp", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("wisp"));

        e.with<game::Enemy>();
        e.with<game::Health>(2, 2);
        e.with<game::Attack>(1);
    });

    auto TREE = registry->register_blueprint("tree", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("tree"));
        e.with<base::CastShadow>(12, utils::Vec2f{});

        Stack tree(Item("log", registry->texture("log")), 12);
        e.with<game::Breakable>(tree, 5);
    });

    auto PINE = registry->register_blueprint("pine", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("pine"));
        e.with<base::CastShadow>(12, utils::Vec2f{});

        Stack tree(Item("log", registry->texture("log")), 12);
        e.with<game::Breakable>(tree, 5);
    });

    auto PALM = registry->register_blueprint("palm", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("palm"));
        e.with<base::CastShadow>(16, utils::Vec2f{});

        Stack tree(Item("log", registry->texture("log")), 12);
        e.with<game::Breakable>(tree, 5);
    });

    auto BUSH = registry->register_blueprint("bush", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("bush"));
    });

    auto GRASS = registry->register_blueprint("grass", [&](core::Builder &e) {
        Stack food(Item("food", registry->texture("food")), 1);
        e.with<game::Breakable>(food, 1);
        e.with<base::Sprite>(registry->texture("grass"));
    });

    auto FLOWER = registry->register_blueprint("flower", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("flower"));
    });

    auto ROCK = registry->register_blueprint("rock", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("rock"));
    });

    auto CACTUS = registry->register_blueprint("cactus", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("cactus"));
    });

    registry->register_biome({
        "taiga",
        {registry->texture("grass-tile"), 0},
        core::TEM{-0.25, 0.5, 0.25},
        {
            {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, PINE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, FLOWER, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {0.5, BUSH, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {1, BUNNY, 0.01, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "forest",
        {registry->texture("grass-tile"), 0},
        core::TEM{0, 0.25, 0.5},
        {
            {1, TREE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, ZOMBIE, 0.1, utils::Noise{0x404c09fa, 1, 2}},
            {0.1, HEDGEHOG, 1, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "jungle",
        {registry->texture("grass-tile"), 0},
        core::TEM{0.5, 0.5, 0.5},
        {
            {1, SLIME, 0.03, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "tundra",
        {registry->texture("snow-tile"), 0},
        core::TEM{-0.5, 0, 0},
        {
            {1, PINE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, BIG_SLIME, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, BUNNY, 0.01, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "plain",
        {registry->texture("grass-tile"), 0},
        core::TEM{0, 0.01, 0},
        {
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, FLOWER, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {0.5, BUSH, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {0.2, SKELETON, 0.2, utils::Noise{0x404c09fa, 1, 2}},
            {1, BUNNY, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "desert",
        {registry->texture("sand-tile"), 0},
        core::TEM{0.5, 0, -0.5},
        {
            {1, CACTUS, 0.1, utils::Noise{0x404c09fa, 1, 2}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {0.2, ZOMBIE, 0.2, utils::Noise{0x404c09fa, 1, 2}},
            {0.2, SKELETON, 0.2, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "swamp",
        {registry->texture("swamp-grass-tile"), 0},
        core::TEM{0.25, 0.1, 1},
        {
            {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "beach",
        {registry->texture("beach-sand-tile"), 0},
        core::TEM{0, -0.1, 0},
        {
            {1, SLIME, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, PALM, 0.5, utils::Noise{0x404c09fa, 1, 0.1}},
        },
    });

    registry->register_biome({
        "stone_beach",
        {registry->texture("stone-tile"), 0},
        core::TEM{-0.5, -0.15, 0},
        {
            {1, SKELETON, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, ROCK, 0.5, utils::Noise{0x404c09fa, 1, 1}},
        },
    });

    registry->register_biome({
        "sea",
        {registry->texture("water-tile"), 0},
        core::TEM{0, -0.2, 0},
        {},
    });

    registry->register_biome({
        "deep_sea",
        {registry->texture("deep-water-tile"), 0},
        core::TEM{0, -0.5, 0},
        {},
    });

    registry->register_biome({
        "cold_sea",
        {registry->texture("water-tile"), 0},
        core::TEM{-0.5, -0.2, 0},
        {},
    });

    registry->register_biome({
        "cold_deep_sea",
        {registry->texture("deep-water-tile"), 0},
        core::TEM{-0.5, -0.5, 0},
        {},
    });

    registry->register_biome({
        "warm_sea",
        {registry->texture("water-tile"), 0},
        core::TEM{0.5, -0.2, -0.5},
        {},
    });

    registry->register_biome({
        "warm_deep_sea",
        {registry->texture("deep-water-tile"), 0},
        core::TEM{0.5, -0.5, -0.5},
        {},
    });

    return registry;
}