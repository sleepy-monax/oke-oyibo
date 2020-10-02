#pragma once

#include <raylib.h>

#include "core/components/Acceleration.h"
#include "core/components/Position.h"
#include "core/components/Velocity.h"
#include "core/debug/FPSCounter.h"
#include "core/debug/Inspector.h"
#include "core/debug/Profiler.h"
#include "core/game/RenderContext.h"
#include "core/game/UpdateContext.h"
#include "core/glue/Glue.h"
#include "core/world/World.h"

#include "editor/Panel.h"

namespace editor
{
    class Editor
    {
    private:
        int _view_port_width = 128;
        int _view_port_height = 128;

        core::world::World &_world;
        core::game::RenderContext _render_context{};

        core::debug::FPSCounter fps_counter{};

        core::debug::Profiler frame_time_profiler{"Frame Time"};
        core::debug::Profiler update_profiler{"Update"};
        core::debug::Profiler render_profiler{"Render"};
        core::debug::Profiler display_profiler{"Display"};

        entt::entity _inspector_selected;
        MM::EntityEditor<entt::entity> _inspector{};

        utils::Vector<utils::OwnPtr<Panel>> _panels;

    public:
        Editor(core::world::World &world)
            : _world(world)
        {
            _inspector.registerComponent<core::components::Velocity>("Velocity");
            _inspector.registerComponent<core::components::Position>("Position");
            _inspector.registerComponent<core::components::Acceleration>("Acceleration");
        }

        ~Editor() {}

        template <typename TPanel, typename... TArgs>
        void open(TArgs &&... args)
        {
            _panels.push_back(utils::own<TPanel>(*this, std::forward<TArgs>(args)...));
        }

        void run()
        {
            frame_time_profiler.mesure([&]() {
                _render_context.resize_to_fit(_view_port_width, _view_port_height);

                update_profiler.mesure([&]() {
                    update();
                });

                render_profiler.mesure([&]() {
                    render();
                });

                display_profiler.mesure([&]() {
                    display();
                });
            });
        }

        void update()
        {
            core::game::UpdateContext context{GetFrameTime(), GetTime()};
            _world.update(context);
        }

        void render()
        {
            _render_context.clear();

            _world.render(_render_context);

            _render_context.compose();
        }

        void display()
        {
            ImGui::DockSpaceOverViewport();

            _panels.foreach ([](auto &panel) {
                panel->do_display();

                return utils::Iteration::CONTINUE;
            });

            ImGui::Begin("Viewport");

            ImGui::GetWindowSize();
            auto size = ImGui::GetWindowSize();

            _view_port_width = size.x;
            _view_port_height = size.y;

            _render_context.composite().display(1);

            ImGui::End();

            ImGui::Begin("Profiler");
            fps_counter.mesure_and_display();
            frame_time_profiler.display();
            update_profiler.display();
            render_profiler.display();
            display_profiler.display();
            ImGui::End();

            _inspector.renderSimpleCombo(_world.entities(), _inspector_selected);
            _render_context.display();
            _world.display();
        }
    };
} // namespace editor
