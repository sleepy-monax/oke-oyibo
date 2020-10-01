#pragma once

#include <raylib.h>

#define ltrace(__args...) TraceLog(LOG_TRACE, __args)
#define ldebug(__args...) TraceLog(LOG_DEBUG, __args)
#define linfo(__args...) TraceLog(LOG_INFO, __args)
#define lwarning(__args...) TraceLog(LOG_WARNING, __args)
#define lerror(__args...) TraceLog(LOG_ERROR, __args)
#define lfatal(__args...) TraceLog(LOG_FATAL, __args)