#pragma once

#include "zero/export.h"

#include <stdint.h>

struct zero_os_timer_t
{
	uint64_t ticks;
};

struct zero_os_microseconds_t
{
	uint64_t ms;
};

ZERO_API zero_os_timer_t
zero_os_timer_start(void);

ZERO_API zero_os_microseconds_t
zero_os_timer_end(zero_os_timer_t self);

ZERO_API void
zero_os_timer_period(uint32_t period);

ZERO_API void
zero_os_timer_sleep(uint32_t milliseconds);
