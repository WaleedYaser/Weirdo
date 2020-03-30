#ifndef KURO_OS_BITMAP_H
#define KURO_OS_BITMAP_H

#include "kuro/export.h"

#include <windows.h>
#include <stdint.h>

typedef struct _kuro_os_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} kuro_os_color_t;

typedef struct _kuro_os_bitmap {
	BITMAPINFO bmi;
	uint32_t *data;
	int width;
	int height;
} kuro_os_bitmap_t;

KURO_EXPORT kuro_os_bitmap_t
kuro_os_bitmap_new(int width, int height);

KURO_EXPORT void
kuro_os_bitmap_free(kuro_os_bitmap_t *self);

KURO_EXPORT void
kuro_os_bitmap_resize(kuro_os_bitmap_t *self, int width, int height);

KURO_EXPORT void
kuro_os_bitmap_fill(kuro_os_bitmap_t *self, kuro_os_color_t color);

KURO_EXPORT void
kuro_os_bitmap_set(kuro_os_bitmap_t *self, int x, int y, kuro_os_color_t color);

#endif /* KURO_OS_BITMAP_H */

