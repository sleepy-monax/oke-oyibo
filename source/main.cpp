#include <raylib.h>

#include "glue/Glue.h"

int main(void)
{
    glue::initialize();

    while (!glue::should_exit())
    {
        glue::begin_frame();

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        glue::end_frame();
    }

    glue::uninitialize();

    return 0;
}