#pragma once

namespace core::glue
{
    void initialize();

    void begin_frame();

    bool should_exit();

    void end_frame();

    void uninitialize();
} // namespace core::glue
