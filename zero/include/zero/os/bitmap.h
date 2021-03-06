#pragma once

#include "zero/export.h"
#include "zero/color.h"

#include <windows.h>

struct zero_os_bitmap_t
{
	BITMAPINFO bmi;
	DWORD *data;
	int width;
	int height;
};

ZERO_API zero_os_bitmap_t
zero_os_bitmap_new(int width, int height);

ZERO_API void
zero_os_bitmap_free(zero_os_bitmap_t *self);

ZERO_API void
zero_os_bitmap_fill(zero_os_bitmap_t *self, zero_color_t color);

inline static zero_color_t
zero_os_bitmap_pixel_get(zero_os_bitmap_t *self, int x, int y)
{
	DWORD raw = self->data[x + y * self->width];
	zero_color_t color;
	color.a = (float)((raw & 0xFF000000) >> 24);
	color.r = (float)((raw & 0x00FF0000) >> 16);
	color.g = (float)((raw & 0x0000FF00) >>  8);
	color.b = (float)((raw & 0x000000FF) >>  0);
	return color;
}

inline static void
zero_os_bitmap_pixel_set(zero_os_bitmap_t *self, int x, int y, zero_color_t color)
{
	self->data[x + y * self->width] =
		((uint8_t)color.a) << 24 |
		((uint8_t)color.r) << 16 |
		((uint8_t)color.g) <<  8 |
		((uint8_t)color.b) <<  0 ;
}

inline static void
zero_os_bitmap_pixel_blend(zero_os_bitmap_t *self, int x, int y, zero_color_t color)
{
	zero_color_t current = zero_os_bitmap_pixel_get(self, x, y);
	zero_color_t blended = zero_color_lerp(current, color, color.a / 255.0f);

	self->data[x + y * self->width] =
		((uint8_t)blended.a) << 24 |
		((uint8_t)blended.r) << 16 |
		((uint8_t)blended.g) <<  8 |
		((uint8_t)blended.b) <<  0 ;
}

inline static void
zero_os_bitmap_fill_rect(
	zero_os_bitmap_t *self,
	float tl_x, float tl_y, float br_x, float br_y,
	zero_color_t color)
{
	for (int j = (int)tl_y; j < (int)br_y; ++j)
		for (int i = (int)tl_x; i < (int)br_x; ++i)
			zero_os_bitmap_pixel_set(self, i, j, color);
}

inline static void
zero_os_bitmap_fill_circle(zero_os_bitmap_t *self, int center_x, int center_y, int radius, zero_color_t color)
{
	int radius_squared = radius * radius;
	for (int j = center_y - radius; j < center_y + radius; ++j)
	{
		for (int i = center_x - radius; i < center_x + radius; ++i)
		{
			float dist_x = i + 0.5f - center_x;
			float dist_y = j + 0.5f - center_y;
			float distance = dist_x * dist_x + dist_y * dist_y;
			if (distance <= radius_squared)
				zero_os_bitmap_pixel_set(self, i, j, color);
		}
	}
}
