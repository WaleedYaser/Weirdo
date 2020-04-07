#ifndef KURO_RASTER_H
#define KURO_RASTER_H

#include "kuro/export.h"

#include <zero/os/bitmap.h>

struct vec2
{
	float x, y;
};

union vec3
{
	struct
	{
		float x, y, z;
	};

	struct
	{
		float r, g, b;
	};
};

struct kuro_triangle_t
{
	vec2 p1, p2, p3;
	vec3 c1, c2, c3;
};

struct kuro_rect_t
{
	vec2 p1, p2, p3, p4;
	vec3 c1, c2, c3, c4;
};

struct kuro_circle_t
{
	vec2 center;
	float radius;
	vec3 color;
};

KURO_API void
kuro_raster_triangle(zero_os_bitmap_t *bitmap, kuro_triangle_t triangle);

KURO_API void
kuro_raster_rect(zero_os_bitmap_t *bitmap, kuro_rect_t rect);

KURO_API void
kuro_raster_circle(zero_os_bitmap_t *bitmap, kuro_circle_t circle);

#endif
