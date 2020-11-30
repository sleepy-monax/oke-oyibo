#pragma once

#include "utils/Common.h"
#include "utils/Rect.h"

namespace core::glue
{
    uint64_t current_frame();

    void initialize();

    void begin_frame();

    bool should_exit();

    void end_frame();

    void uninitialize();

    utils::Rectf screen();
} // namespace core::glue
