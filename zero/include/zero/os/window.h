#ifndef ZERO_OS_WINDOW_H
#define ZERO_OS_WINDOW_H

#pragma comment(lib, "User32.lib")

#include "zero/export.h"
#include "zero/os/bitmap.h"

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _zero_os_window_message {
	bool quit;
	int  window_width;
	int  window_height;
} zero_os_window_message_t;

typedef struct _zero_os_window {
	HWND hwnd;
} zero_os_window_t;

ZERO_API zero_os_window_t
zero_os_window_create(void);

ZERO_API void
zero_os_window_destroy(zero_os_window_t self);

ZERO_API zero_os_window_message_t
zero_os_window_message(zero_os_window_t self);

ZERO_API void
zero_os_window_fill(zero_os_window_t self, const zero_os_bitmap_t *bitmap);

#endif /* ZERO_OS_WINDOW_H */
