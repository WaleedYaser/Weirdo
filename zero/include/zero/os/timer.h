#ifndef ZERO_OS_TIMER_H
#define ZERO_OS_TIMER_H

#include "zero/export.h"

#include <stdint.h>

typedef struct _zero_os_timer {
	uint64_t ticks;
} zero_os_timer_t;

typedef struct _zero_os_microseconds {
	uint64_t ms;
} zero_os_microseconds_t;

ZERO_API zero_os_timer_t
zero_os_timer_start(void);

ZERO_API zero_os_microseconds_t
zero_os_timer_end(zero_os_timer_t self);

ZERO_API void
zero_os_timer_sleep(uint32_t milliseconds);

#endif /* ZERO_OS_TIMER_H */
