#include <imgui.h>
#include <raylib.h>

#include "core/Director.h"

#include "game/Registry.h"
#include "game/scene/SplashScreen.h"

int main()
{
    core::glue::initialize();

    auto registry = game::make_registry();

    core::Director director{registry};

    director.switch_scene<game::SplashScreen>();

    SetExitKey(KEY_F4);

    while (!core::glue::should_exit())
    {
        core::glue::begin_frame();

        director.run();

        core::glue::end_frame();
    }

    core::glue::uninitialize();

    return 0;
}
