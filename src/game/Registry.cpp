#include "game/Registry.h"

#include "base/components/CastShadow.h"
#include "base/components/Colider.h"
#include "base/components/LightSource.h"
#include "base/components/Momentum.h"
#include "base/components/Move.h"
#include "base/components/Player.h"
#include "base/components/Position.h"
#include "base/components/Sprite.h"

#include "game/components/Animal.h"
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
#include "game/components/Menu.h"
#include "game/components/Pickable.h"
#include "game/components/Prey.h"
#include "game/components/Stamina.h"
#include "game/components/Difficulty.h"

#include "base/systems/Camera.h"
#include "base/systems/EntityRenderer.h"
#include "base/systems/Input.h"
#include "base/systems/Light.h"
#include "base/systems/Movement.h"
#include "base/systems/Physic.h"
#include "base/systems/Shadow.h"
#include "base/systems/TerrainRender.h"

#include "game/systems/AnimalMove.h"
#include "game/systems/AttackSystem.h"
#include "game/systems/BreakableSystem.h"
#include "game/systems/DrinkSystem.h"
#include "game/systems/EatSystem.h"
#include "game/systems/EnemyMove.h"
#include "game/systems/HealthBar.h"
#include "game/systems/HoldItemSystem.h"
#include "game/systems/HungerSystem.h"
#include "game/systems/InventorySystem.h"
#include "game/systems/MenuSystem.h"
#include "game/systems/RegenSystem.h"
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
    registry->register_system<game::StaminaSystem>("stamina");
    registry->register_system<game::ThirstSystem>("thirst");
    registry->register_system<game::RegenSystem>("regen");
    registry->register_system<game::HoldItemSystem>("hold-item");
    registry->register_system<game::AttackSystem>("attack");
    registry->register_system<game::EatSystem>("eat");
    registry->register_system<game::DrinkSystem>("drink");
    registry->register_system<game::MenuSystem>("menu");
    registry->register_system<game::AnimalMove>("animal");

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
    registry->register_component<game::Animal>("animal");
    registry->register_component<game::Difficulty>("difficulty");

    Item ITEM_LOG{"log", registry->texture("log")};
    Item ITEM_BURGER{"burger", registry->texture("food"), Item::FOOD};
    Item ITEM_STICK{"stick", registry->texture("stick")};
    Item ITEM_ROCK{"rock", registry->texture("rock")};
    Item ITEM_FLOWER{"flower", registry->texture("flower")};
    Item ITEM_SWORD{"sword", registry->texture("sword")};
    Item ITEM_BONE{"bone", registry->texture("bone")};
    Item ITEM_SLIME_BALL{"slime-ball", registry->texture("slime-ball")};
    Item ITEM_SHARK_FIN{"shark-fin", registry->texture("shark-fin")};
    Item ITEM_APPLE{"apple", registry->texture("apple"), Item::FOOD};
    Item ITEM_THORN{"hedgehog-thorn", registry->texture("hedgehog-thorn")};
    Item ITEM_MEAT{"meat", registry->texture("meat"), Item::FOOD};
    Item ITEM_WOOL{"wool", registry->texture("wool")};
    Item ITEM_COCO{"coconut", registry->texture("coconut")};
    Item ITEM_FLOUR{"flour", registry->texture("flour")};

    game::Difficulty difficulty;

    registry->register_craft({
        .result = {ITEM_STICK, 4},
        .ingredients = {
            {ITEM_LOG, 1},
        },
    });

    registry->register_craft({
        {ITEM_SWORD, 1},
        {
            {ITEM_STICK, 1},
            {ITEM_ROCK, 2},
        },
    });

    auto PLAYER = registry->register_blueprint("player", [&](core::Builder &e) {
        e.with<base::CastShadow>(4, utils::Vec2f{0.5, 0});
        e.with<base::LightSource>(128.0f, WHITE);
        e.with<base::Momentum>();
        e.with<base::Player>(0);
        e.with<base::Sprite>(registry->texture("character"));
        e.with<game::Attack>(2);
        e.with<game::Health>(10, 10);
        e.with<game::HoldItem>();
        e.with<game::Hunger>(20.0f, 20.0f);
        e.with<game::Inventory>();
        e.with<base::Move>();
        e.with<game::Prey>();
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Stamina>(20.0f, 20.0f);
        e.with<game::Thirst>(20.0f, 20.0f);
        e.with<game::Menu>();
    });

    auto HEDGEHOG = registry->register_blueprint("hedgehog", [&, ITEM_THORN, ITEM_MEAT](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("hedgehog"));
        e.with<base::CastShadow>(4, utils::Vec2f{-1, 0});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Animal>();
        e.with<game::Inventory>(game::Inventory{{{ITEM_THORN, 2}, {ITEM_MEAT, 1}}});

        e.with<game::Health>(7, 7);
    });

    auto BUNNY = registry->register_blueprint("bunny", [&, ITEM_MEAT](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("bunny"));
        e.with<base::CastShadow>(4, utils::Vec2f{-1, 0});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Animal>();
        e.with<game::Inventory>(game::Inventory{{{ITEM_MEAT, 1}}});

        e.with<game::Health>(7, 7);
    });

    auto SHEEP = registry->register_blueprint("sheep", [&, ITEM_MEAT, ITEM_WOOL](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("sheep"));
        e.with<base::CastShadow>(4, utils::Vec2f{-1, 0});
        e.with<game::Animal>();
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Inventory>(game::Inventory{{{ITEM_MEAT, 2}, {ITEM_WOOL, 1}}});

        e.with<game::Health>(7, 7);
    });

    auto ZOMBIE = registry->register_blueprint("zombie", [&, ITEM_STICK, ITEM_ROCK](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("zombie"));
        e.with<base::CastShadow>(4, utils::Vec2f{0.5, 0});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Inventory>(game::Inventory{{{ITEM_STICK, 2},{ITEM_ROCK, 2}}});

        e.with<game::Enemy>();
        e.with<game::Health>(7, 7);
        e.with<game::Attack>(1+difficulty.value);
    });

    auto SKELETON = registry->register_blueprint("skeleton", [&, ITEM_BONE](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("skeleton"));
        e.with<base::CastShadow>(4, utils::Vec2f{0.5, 0});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
        e.with<game::Inventory>(game::Inventory{{{ITEM_BONE, 2}}});

        e.with<game::Enemy>();
        e.with<game::Health>(6, 6);
        e.with<game::Attack>(1+difficulty.value);
    });

    auto SLIME = registry->register_blueprint("slime", [&, ITEM_SLIME_BALL](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.05);
        e.with<base::Sprite>(registry->texture("slime"));
        e.with<base::CastShadow>(8, utils::Vec2f{0, 0});
        e.with<game::Inventory>(game::Inventory{{{ITEM_SLIME_BALL, 3}}});

        e.with<game::Enemy>();
        e.with<game::Health>(3, 3);
        e.with<game::Attack>(1+difficulty.value);
    });

    auto BIG_SLIME = registry->register_blueprint("big-slime", [&, ITEM_SLIME_BALL](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("big-slime"));
        e.with<base::CastShadow>(12, utils::Vec2f{0, 0});
        e.with<game::Inventory>(game::Inventory{{{ITEM_SLIME_BALL, 6}}});

        e.with<game::Enemy>();
        e.with<game::Health>(5, 5);
        e.with<game::Attack>(1+difficulty.value);
    });

    auto WISP = registry->register_blueprint("wisp", [&](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("wisp"));

        e.with<game::Enemy>();
        e.with<game::Health>(2, 2);
        e.with<game::Attack>(1+difficulty.value);
    });

    auto SHARK = registry->register_blueprint("shark", [&, ITEM_SWORD, ITEM_SHARK_FIN](core::Builder &e) {
        e.with<base::Momentum>();
        e.with<base::Move>(0.03);
        e.with<base::Sprite>(registry->texture("shark"));
        e.with<game::Inventory>(game::Inventory{{{ITEM_SWORD, 1}, {ITEM_SHARK_FIN,1}}});

        e.with<game::Enemy>(true);
        e.with<game::Health>(20, 20);
        e.with<game::Attack>(5+difficulty.value);
    });

    auto TREE = registry->register_blueprint("tree", [&, ITEM_LOG, ITEM_APPLE](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("tree"));
        e.with<base::CastShadow>(12, utils::Vec2f{});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);

        e.with<game::Health>(5, 5);
        e.with<game::Inventory>(game::Inventory{{{ITEM_LOG, 4}, {ITEM_APPLE, 1}}});

    });

    auto PINE = registry->register_blueprint("pine", [&, ITEM_LOG](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("pine"));
        e.with<base::CastShadow>(12, utils::Vec2f{});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);

        e.with<game::Health>(5, 5);
        e.with<game::Inventory>(game::Inventory{{{ITEM_LOG, 4}}});
    });

    auto PALM = registry->register_blueprint("palm", [&, ITEM_LOG, ITEM_COCO](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("palm"));
        e.with<base::CastShadow>(16, utils::Vec2f{});
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);

        e.with<game::Health>(5, 5);
        e.with<game::Inventory>(game::Inventory{{{ITEM_LOG, 4}, {ITEM_COCO, 1}}});
    });

    auto BUSH = registry->register_blueprint("bush", [&, ITEM_STICK](core::Builder &e) {
        e.with<game::Health>(1, 1);
        e.with<game::Inventory>(game::Inventory{{{ITEM_STICK, 2}}});
        e.with<base::Sprite>(registry->texture("bush"));
    });

    auto GRASS = registry->register_blueprint("grass", [&, ITEM_BURGER](core::Builder &e) {
        e.with<game::Health>(1, 1);
        e.with<game::Inventory>(game::Inventory{{{ITEM_FLOUR, 1}}});
        e.with<base::Sprite>(registry->texture("grass"));
    });

    auto FLOWER = registry->register_blueprint("flower", [&, ITEM_FLOWER](core::Builder &e) {
        e.with<game::Health>(1, 1);
        e.with<game::Inventory>(game::Inventory{{{ITEM_FLOWER, 1}}});
        e.with<base::Sprite>(registry->texture("flower"));
    });

    auto ROCK = registry->register_blueprint("rock", [&, ITEM_ROCK](core::Builder &e) {
        e.with<game::Health>(1, 1);
        e.with<game::Inventory>(game::Inventory{{{ITEM_ROCK, 1}}});
        e.with<base::Sprite>(registry->texture("rock"));
    });

    auto CACTUS = registry->register_blueprint("cactus", [&](core::Builder &e) {
        e.with<base::Sprite>(registry->texture("cactus"));
        e.with<base::Colider>(-2.0f, -2.0f, 4.0f, 4.0f);
    });

    auto DEAD_BUSH = registry->register_blueprint("dead-bush", [&, ITEM_STICK](core::Builder &e) {
        e.with<game::Health>(1, 1);
        e.with<game::Inventory>(game::Inventory{{{ITEM_STICK, 1}}});
        e.with<base::Sprite>(registry->texture("dead-bush"));
        e.with<base::CastShadow>(4, utils::Vec2f{0, 0});
    });

    core::Tile WATER_TILE{registry->texture("water-tile"), core::Tile::LIQUID};
    core::Tile GRASS_TILE{registry->texture("grass-tile"), core::Tile::SOLID};
    core::Tile SNOW_TILE{registry->texture("snow-tile"), core::Tile::SOLID};
    core::Tile SAND_TILE{registry->texture("sand-tile"), core::Tile::SOLID};
    // core::Tile SWAMP_GRASS_TILE{registry->texture("swamp-grass-tile"), core::Tile::SOLID};
    core::Tile BEACH_SAND_TILE{registry->texture("beach-sand-tile"), core::Tile::SOLID};
    core::Tile STONE_TILE{registry->texture("stone-tile"), core::Tile::SOLID};
    core::Tile DEEP_WATER_TILE{registry->texture("deep-water-tile"), core::Tile::LIQUID};

    registry->register_biome({
        "taiga",
        GRASS_TILE,
        core::TEM{-0.25, 0.5, 0.25},
        {
            {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, PINE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, FLOWER, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {0.5, BUSH, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {1, BUNNY, 0.05, utils::Noise{0x404c09fa, 1, 2}},
            {1, SHEEP, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "forest",
        GRASS_TILE,
        core::TEM{0, 0.25, 0.5},
        {
            {1, TREE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, ZOMBIE, 0.1, utils::Noise{0x404c09fa, 1, 2}},
            {0.5, HEDGEHOG, 0.1, utils::Noise{0x404c09fa, 1, 2}},
            {1, SHEEP, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    // FIXME: Jungle biome
    // registry->register_biome({
    //     "jungle",
    //     GRASS_TILE,
    //     core::TEM{0.5, 0.5, 0.5},
    //     {
    //         {1, SLIME, 0.03, utils::Noise{0x404c09fa, 1, 2}},
    //     },
    // });

    registry->register_biome({
        "tundra",
        SNOW_TILE,
        core::TEM{-0.5, 0, 0},
        {
            {1, PINE, 1, utils::Noise{0x404c09fa, 1, 0.1}},
            {1, BIG_SLIME, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, BUNNY, 0.02, utils::Noise{0x404c09fa, 1, 2}},
            {1, SHEEP, 0.02, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "plain",
        GRASS_TILE,
        core::TEM{0, 0.01, 0},
        {
            {1, GRASS, 1, utils::Noise{0x404c09fa, 1, 2}},
            {1, FLOWER, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {0.5, BUSH, 0.25, utils::Noise{0x404c09fa, 1, 0.025}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {0.2, SKELETON, 0.2, utils::Noise{0x404c09fa, 1, 2}},
            {1, BUNNY, 0.05, utils::Noise{0x404c09fa, 1, 2}},
            {1, SHEEP, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "desert",
        SAND_TILE,
        core::TEM{0.5, 0, -0.5},
        {
            {1, CACTUS, 0.1, utils::Noise{0x404c09fa, 1, 2}},
            {1, ROCK, 0.1, utils::Noise{0x404c09fa, 1, 1}},
            {0.2, ZOMBIE, 0.2, utils::Noise{0x404c09fa, 1, 2}},
            {0.2, SKELETON, 0.2, utils::Noise{0x404c09fa, 1, 2}},
            {1, DEAD_BUSH, 0.25, utils::Noise{0x404c09fa, 3, 1}},
        },
    });

    // FIXME: swamp biome;
    // registry->register_biome({
    //     "swamp",
    //     SWAMP_GRASS_TILE,
    //     core::TEM{0.25, 0.1, 1},
    //     {
    //         {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
    //     },
    // });

    registry->register_biome({
        "beach",
        BEACH_SAND_TILE,
        core::TEM{0, -0.1, 0},
        {
            {1, SLIME, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, PALM, 0.5, utils::Noise{0x404c09fa, 1, 0.1}},
        },
    });

    registry->register_biome({
        "stone_beach",
        STONE_TILE,
        core::TEM{-0.5, -0.15, 0},
        {
            {1, SKELETON, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, WISP, 0.01, utils::Noise{0x404c09fa, 1, 2}},
            {1, ROCK, 0.5, utils::Noise{0x404c09fa, 1, 1}},
        },
    });

    registry->register_biome({
        "sea",
        WATER_TILE,
        core::TEM{0, -0.2, 0},
        {
            {1, SHARK, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "deep_sea",
        DEEP_WATER_TILE,
        core::TEM{0, -0.5, 0},
        {
            {1, SHARK, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "cold_sea",
        WATER_TILE,
        core::TEM{-0.5, -0.2, 0},
        {},
    });

    registry->register_biome({
        "cold_deep_sea",
        DEEP_WATER_TILE,
        core::TEM{-0.5, -0.5, 0},
        {},
    });

    registry->register_biome({
        "warm_sea",
        WATER_TILE,
        core::TEM{0.5, -0.2, -0.5},
        {
            {1, SHARK, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    registry->register_biome({
        "warm_deep_sea",
        DEEP_WATER_TILE,
        core::TEM{0.5, -0.5, -0.5},
        {
            {1, SHARK, 0.05, utils::Noise{0x404c09fa, 1, 2}},
        },
    });

    return registry;
}