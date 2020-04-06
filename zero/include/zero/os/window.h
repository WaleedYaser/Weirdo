#ifndef ZERO_OS_WINDOW_H
#define ZERO_OS_WINDOW_H

#include "zero/export.h"
#include "zero/window_msg.h"
#include "zero/os/bitmap.h"

#include <windows.h>

typedef struct _zero_os_window {
	HWND hwnd;
} zero_os_window_t;

ZERO_API zero_os_window_t
zero_os_window_create(void);

ZERO_API void
zero_os_window_destroy(zero_os_window_t self);

ZERO_API void
zero_os_window_message(zero_os_window_t self, zero_window_msg_t *window_msg);

ZERO_API void
zero_os_window_fill(zero_os_window_t self, const zero_os_bitmap_t *bitmap);

ZERO_API int
zero_os_window_refresh_rate(zero_os_window_t self);

#endif /* ZERO_OS_WINDOW_H */
