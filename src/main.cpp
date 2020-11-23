#include <imgui.h>
#include <raylib.h>

#include "core/Director.h"
#include "game/scene/InGame.h"
#include "game/scene/MainMenu.h"

int main()
{
    core::glue::initialize();

    core::Director director;

    director.switch_scene(new game::InGame());

    while (!core::glue::should_exit())
    {
        core::glue::begin_frame();

        director.run();

        core::glue::end_frame();
    }

    core::glue::uninitialize();

    return 0;
}
