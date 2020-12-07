#pragma once

#include <string>

#include "utils/Callback.h"
#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/RefCounter.h"

#include "core/Blueprint.h"
#include "core/System.h"
#include "core/Texture.h"
#include "core/world/Biome.h"

#include "game/inventory/Craft.h"
#include "game/inventory/Item.h"

#include "base/components/Component.h"

namespace core
{
    class World;
} // namespace core

namespace core
{
    struct SystemDescription
    {
        std::string name;

        utils::Callback<void(core::World &, core::System &)> inspect;
        utils::Callback<utils::OwnPtr<core::System>()> create;
    };

    struct ComponentDescription
    {
        std::string name;

        utils::Callback<void(core::World &, entt::entity)> inspect;
    };

    struct TextureDescription
    {
        std::string name;
        Texture texture;
    };

    struct FontDescription
    {
        std::string name;
        Font font;
    };

    class Registry: public utils::RefCounted<Registry>
    {
    private:
        utils::HashMap<entt::id_type, SystemDescription> _systems{};
        utils::HashMap<entt::id_type, ComponentDescription> _components{};
        utils::Vector<TextureDescription> _textures;
        utils::Vector<FontDescription> _fonts;
        utils::Vector<Biome> _biomes;
        utils::Vector<game::Craft> _crafts;

        utils::HashMap<std::string, utils::RefPtr<Blueprint>> _blueprints{};

    public:
        Registry() {}

        template <typename TSystem>
        void register_system(const char *name)
        {
            auto id = entt::type_info<TSystem>::id();

            _systems[id] = SystemDescription{
                name,
                [](core::World &w, core::System &s) {
                    inspect_system<TSystem>(w, sketchy_cast<core::System, TSystem>(s));
                },
                []() {
                    return utils::own<TSystem>();
                },
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

            _components[id] = ComponentDescription{
                name,
                [](core::World &w, entt::entity e) {
                    inspect_component<TComponent>(w, e);
                },
            };
        }

        template <typename TCallback>
        void foreach_components(TCallback callback)
        {
            _components.foreach (callback);
        }

        Texture texture(std::string name)
        {
            for (size_t i = 0; i < _textures.count(); i++)
            {
                if (_textures[i].name == name)
                {
                    return _textures[i].texture;
                }
            }

            auto path = "assets/" + name + ".png";
            auto tex = LoadTexture(path.c_str());

            _textures.push_back({name, tex});

            return _textures[_textures.count() - 1].texture;
        }

        Font font(std::string name)
        {
            for (size_t i = 0; i < _fonts.count(); i++)
            {
                if (_fonts[i].name == name)
                {
                    return _fonts[i].font;
                }
            }

            auto path = "assets/" + name + ".ttf";
            auto ttf = LoadFontEx(path.c_str(), 72, nullptr, 0);
            _fonts.push_back({name, ttf});
            return ttf;
        }

        utils::RefPtr<Blueprint> register_blueprint(std::string name, utils::Callback<void(Builder &)> blueprint)
        {
            _blueprints[name] = utils::make<Blueprint>(blueprint);
            return _blueprints[name];
        }

        Blueprint &blueprint(std::string name)
        {
            if (_blueprints.has_key(name))
            {
                return *_blueprints[name];
            }
            else
            {
                assert(false);
                static Blueprint EMPTY_BLUEPRINT;
                return EMPTY_BLUEPRINT;
            }
        }

        void register_biome(Biome biome)
        {
            _biomes.push_back(biome);
        }

        Biome &lookup_biome(TEM tem)
        {
            Biome *best_biome = nullptr;
            double best_distance = 10000000;

            for (size_t i = 0; i < _biomes.count(); i++)
            {
                Biome *biome = &_biomes[i];

                double distance = biome->climat.difference(tem);

                if (distance < best_distance)
                {
                    best_distance = distance;
                    best_biome = biome;
                }
            }

            assert(best_biome != nullptr);

            return *best_biome;
        }

        void register_craft(game::Craft craft)
        {
            _crafts.push_back(craft);
        }

        const utils::Vector<game::Craft> &crafts()
        {
            return _crafts;
        }
    };
} // namespace core
