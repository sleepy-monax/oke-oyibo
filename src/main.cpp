#include <imgui.h>
#include <raylib.h>

#include "core/Director.h"

#include "game/Registery.h"
#include "game/scene/InGame.h"
#include "game/scene/MainMenu.h"

int main()
{
    core::glue::initialize();

    auto registry = game::make_registry();

    core::Director director{registry};

    director.switch_scene<game::MainMenu>();

    while (!core::glue::should_exit())
    {
        core::glue::begin_frame();

        director.run();

        core::glue::end_frame();
    }

    core::glue::uninitialize();

    return 0;
}
