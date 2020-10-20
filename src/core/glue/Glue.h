#pragma once

#include "utils/Common.h"

namespace core::glue
{
    uint64_t current_frame();

    void initialize();

    void begin_frame();

    bool should_exit();

    void end_frame();

    void uninitialize();
} // namespace core::glue
