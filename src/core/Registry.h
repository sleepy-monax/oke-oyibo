#pragma once

#include <functional>
#include <string>

#include "utils/HashMap.h"
#include "utils/OwnPtr.h"
#include "utils/RefCounter.h"

#include "base/components/Component.h"
#include "core/System.h"

namespace core
{
    class World;
} // namespace core

namespace core
{
    struct SystemDescription
    {
        std::string name;

        std::function<void(core::World &, core::System &)> inspect;
        std::function<utils::OwnPtr<core::System>()> create;
    };

    struct ComponentDescription
    {
        std::string name;

        std::function<void(core::World &, entt::entity)> inspect;
    };

    struct TextureDescription
    {
        std::string name;
        Texture2D texture;
    };

    struct FontDescription
    {
        std::string name;
        Font font;
    };

    using TextureHandle = int;
    using FontHandle = int;

    class Registry: public utils::RefCounted<Registry>
    {
    private:
        utils::HashMap<entt::id_type, SystemDescription> _systems{};
        utils::HashMap<entt::id_type, ComponentDescription> _components{};
        utils::Vector<TextureDescription> _textures;
        utils::Vector<FontDescription> _fonts;

    public:
        Registry() {}

        template <typename TSystem>
        void register_system(const char *name)
        {
            auto id = entt::type_info<TSystem>::id();

            auto inspect_wrapper = [](core::World &w, core::System &s) {
                inspect_system<TSystem>(w, sketchy_cast<core::System, TSystem>(s));
            };

            auto create_wrapper = []() {
                return utils::own<TSystem>();
            };

            _systems[id] = SystemDescription{
                name,
                inspect_wrapper,
                create_wrapper,
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

            auto inspect_wrapper = [](core::World &w, entt::entity e) {
                inspect_component<TComponent>(w, e);
            };

            _components[id] = ComponentDescription{name, inspect_wrapper};
        }

        template <typename TCallback>
        void foreach_components(TCallback callback)
        {
            _components.foreach (callback);
        }

        TextureHandle register_texture(std::string name)
        {
            auto path = "assets/" + name + ".png";
            auto tex = LoadTexture(path.c_str());

            _textures.push_back({name, tex});

            return _textures.count() - 1;
        }

        const Texture2D &texture(TextureHandle hnd)
        {
            return _textures[hnd].texture;
        }

        FontHandle register_font(std::string name)
        {
            auto path = "assets/" + name + ".ttf";
            auto ttf = LoadFont(path.c_str());

            _fonts.push_back({name, ttf});
            return _fonts.count() - 1;
        }

        const Font &font(FontHandle hnd)
        {
            return _fonts[hnd].font;
        }
    };
} // namespace core
