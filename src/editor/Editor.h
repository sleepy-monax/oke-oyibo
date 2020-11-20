#pragma once

#include <raylib.h>

#include "base/components/Acceleration.h"
#include "base/components/Position.h"
#include "base/components/Velocity.h"
#include "core/Probe.h"
#include "core/Time.h"
#include "core/World.h"
#include "core/glue/Glue.h"
#include "core/glue/ImGuiExtension.h"

#include "editor/FPSCounter.h"
#include "editor/Panel.h"

namespace editor
{
    class Editor
    {
    private:
        int _view_port_width = 128;
        int _view_port_height = 128;

        core::World &_world;
        core::Camera _camera{};

        editor::FPSCounter fps_counter{};

        core::Probe frame_time_probe{"Frame Time"};
        core::Probe update_probe{"Update"};
        core::Probe render_probe{"Render"};
        core::Probe display_probe{"Display"};

        utils::Vector<utils::OwnPtr<Panel>> _panels{};

    public:
        auto &world() { return _world; }
        auto &entities() { return _world.entities(); }
        auto &system() { return _world.systems(); }
        auto &registry() { return _world.registry(); }

        Editor(core::World &world)
            : _world(world)
        {
        }

        ~Editor() {}

        template <typename TPanel, typename... TArgs>
        TPanel &open(TArgs &&... args)
        {
            auto ptr = utils::own<TPanel>(*this, std::forward<TArgs>(args)...);
            auto &ref = *ptr;
            _panels.push_back(ptr);
            return ref;
        }

        void run()
        {
            fps_counter.mesure_fps();

            frame_time_probe.mesure_time([&]() {
                _camera.resize_to_fit(_view_port_width, _view_port_height);

                update_probe.mesure_time([&]() {
                    update();
                });

                render_probe.mesure_time([&]() {
                    render();
                });

                display_probe.mesure_time([&]() {
                    display();
                });
            });
        }

        void update()
        {
            core::Time time{GetFrameTime(), GetTime()};
            _world.update(time);

            _panels.foreach ([&](auto &panel) {
                panel->update(time);

                return utils::Iteration::CONTINUE;
            });
        }

        void render()
        {
            _camera.clear();

            _world.render(_camera);

            _panels.foreach ([](auto &panel) {
                panel->render();

                return utils::Iteration::CONTINUE;
            });

            _camera.compose();
        }

        void display()
        {
            ImGui::DockSpaceOverViewport();

            _panels.foreach ([](auto &panel) {
                panel->do_display();

                return utils::Iteration::CONTINUE;
            });

            ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            ImGui::SetScrollX(0);
            ImGui::SetScrollY(0);

            ImGui::GetWindowSize();
            auto size = ImGui::GetWindowSize();

            _view_port_width = size.x;
            _view_port_height = size.y;

            ImGui::Viewport(reinterpret_cast<void *>(_camera.composite().underlying_texture().id), ImVec2(_camera.composite().width(), _camera.composite().height()));

            ImGui::End();

            ImGui::Begin("Profiler");
            inspect(fps_counter);
            inspect(frame_time_probe);
            inspect(update_probe);
            inspect(render_probe);
            inspect(display_probe);
            ImGui::End();

            _camera.display();
        }
    };
} // namespace editor
