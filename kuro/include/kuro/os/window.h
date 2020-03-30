#ifndef KURO_OS_WINDOW_H
#define KURO_OS_WINDOW_H

#include "kuro/export.h"
#include "kuro/os/bitmap.h"

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _kuro_os_window_message {
	bool quit;
	int  window_width;
	int  window_height;
} kuro_os_window_message_t;

typedef struct _kuro_os_window {
	HWND hwnd;
} kuro_os_window_t;

KURO_EXPORT kuro_os_window_t
kuro_os_window_create(void);

KURO_EXPORT void
kuro_os_window_destroy(kuro_os_window_t self);

KURO_EXPORT kuro_os_window_message_t
kuro_os_window_message(kuro_os_window_t self);

KURO_EXPORT void
kuro_os_window_fill(kuro_os_window_t self, const kuro_os_bitmap_t *bitmap);

#endif /* KURO_OS_WINDOW_H */
