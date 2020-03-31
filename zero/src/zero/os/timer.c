#include "zero/os/timer.h"

#include <windows.h>

zero_os_timer_t
zero_os_timer_start(void)
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter(&ticks);
	return (zero_os_timer_t) {.ticks = ticks.QuadPart};
}

zero_os_microseconds_t
zero_os_timer_end(zero_os_timer_t self)
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER end_ticks;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&end_ticks);
	return (zero_os_microseconds_t) {
		.ms = ((end_ticks.QuadPart - self.ticks) * 1000000) / frequency.QuadPart};
}

void
zero_os_timer_period(uint32_t period)
{
	MMRESULT res = timeBeginPeriod(period);
	assert(res == TIMERR_NOERROR);
}

void
zero_os_timer_sleep(uint32_t milliseconds)
{
	Sleep(milliseconds);
}

