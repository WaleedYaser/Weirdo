#ifndef ZERO_OS_BITMAP_H
#define ZERO_OS_BITMAP_H

#pragma comment(lib, "Gdi32.lib")

#include "zero/export.h"

#include <windows.h>
#include <stdint.h>

typedef struct _zero_os_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} zero_os_color_t;

typedef struct _zero_os_bitmap {
	BITMAPINFO bmi;
	uint32_t *data;
	int width;
	int height;
} zero_os_bitmap_t;

ZERO_API zero_os_bitmap_t
zero_os_bitmap_new(int width, int height);

ZERO_API void
zero_os_bitmap_free(zero_os_bitmap_t *self);

ZERO_API void
zero_os_bitmap_resize(zero_os_bitmap_t *self, int width, int height);

ZERO_API void
zero_os_bitmap_fill(zero_os_bitmap_t *self, zero_os_color_t color);

ZERO_API void
zero_os_bitmap_set(zero_os_bitmap_t *self, int x, int y, zero_os_color_t color);

#endif /* ZERO_OS_BITMAP_H */

